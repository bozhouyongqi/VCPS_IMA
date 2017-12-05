#ifndef _OPERATE_FUN_H
#define _OPERATE_FUN_H
void calIndiviualFitness(int index);

void generateMemoryRepo(){
	// 根据适应度对前PUM个个体排序
	Individual temp;
	for(int i = 0; i < P_NUM -1 ; i++) {
		for (int j = i + 1; j < P_NUM; j++) {
			if(pop[i].weightedValue > pop[j].weightedValue) {
				temp = pop[i];
				pop[i] = pop[j];
				pop[j] = temp;
			}
		}
	}
	for (int i = P_NUM; i < P_NUM + MEM_NUM; i++) {
		pop[i] = pop[i - P_NUM];
	}
}

void generateVaccine(){
	for (int taskNum = 0; taskNum < TASK_NUM; taskNum++) {
		for (int agentNum = 0; agentNum < AGENT_ALL; agentNum++) {
			int sum = 0;
			for(int ind = P_NUM; ind < P_NUM + MEM_NUM; ind ++) {
				sum += pop[ind].encode[taskNum][agentNum];
			}
			if (sum == MEM_NUM) {
				Vaccine[taskNum][agentNum] = 1; // 
			}else if (sum == 0){
				Vaccine[taskNum][agentNum] = 0;
			}else {
				Vaccine[taskNum][agentNum] = -1;
			}
		}
	}
}

void cross(){

	int i,j,k,y,(*par1)[AGENT_ALL],(*par2)[AGENT_ALL];
	double rnd;

	int index_row=0;
	int index_col=0;
	int index_num=0;

	int temp=0;
	Individual *ind_ptr;

	rnd=(double)rand()/RAND_MAX;  

	ind_ptr=&(pop[0]); 

	for (i = 0,y = 0;i < P_NUM/2;i++)
	{
		ind_ptr = &(pop[y]);
		par1 = ind_ptr->encode;
		y = y+1;

		ind_ptr = &(pop[y]);
		par2 = ind_ptr->encode; 
		y = y+1;

		rnd = (double)rand()/RAND_MAX;
		if (rnd < Cross_pro)
		{
			index_row=rand()%(AGENT_ALL-1)+1;//产生1到AGENT_ALL-1之间的随机数，包含1而不包含AGENT_ALL-1
			index_col=rand()%(TASK_NUM-1)+1;

			for ( j=0;j<index_row;j++)
				for ( k=0;k<index_col;k++)
				{
					temp=  *(*(par1+k)+j)   ;

					*(*(par1+k)+j)=*(*(par2+k)+j);

					*(*(par2+k)+j)=temp;
				}

				for (j=index_row;j<AGENT_ALL;j++)
					for ( k=index_col;k<TASK_NUM;k++)
					{
						temp=  *(*(par1+k)+j)   ;

						*(*(par1+k)+j)=*(*(par2+k)+j);

						*(*(par2+k)+j)=temp;
					} 
		}
	}
}

void mutate() {
	int index_agt1=0;
	int index_agt2=0;

	int index_tsk1=0;
	int index_tsk2=0;

	int temp=0;

	Individual *ind_ptr;

	double num_rnd=0;

	int (*mut_ptr)[AGENT_ALL];

	ind_ptr = &(pop[0]);

	for (int k=0;k<P_NUM;k++)
	{
		ind_ptr=&(pop[k])	;
		mut_ptr=ind_ptr->encode;

		num_rnd=(double)rand()/RAND_MAX; ;

		if (num_rnd < Mutate_pro)
		{

			index_agt1=rand()%AGENT_ALL;
			index_agt2=rand()%AGENT_ALL;

			index_tsk1=rand()%TASK_NUM;
			index_tsk2=rand()%TASK_NUM;

			if(index_agt1>index_agt2)
			{
				temp=index_agt1;
				index_agt1=index_agt2;
				index_agt2=temp;
			}

			if(index_tsk1>index_tsk2)
			{
				temp=index_tsk1;
				index_tsk1=index_tsk2;
				index_tsk2=temp;
			}

			int bit=0;

			for (int i=index_tsk1;i<=index_tsk2;i++)
				for (int j=index_agt1;j<=index_agt2;j++)
				{
					bit=*(*(mut_ptr+i)+j);
					if (bit==0)
						*(*(mut_ptr+i)+j)=1;

					if (bit==1)
						*(*(mut_ptr+i)+j)=0;
				}	
		}
	}
}	

void inoculateAntibody() {
	Individual temp;
	double rnd;
	for (int i = 0; i < P_NUM; i++) {
		calIndiviualFitness(i); // 逐个个体计算适应度
	}
	for (int ind = 0; ind < P_NUM; ind ++) {
		rnd = (double)rand()/RAND_MAX;
		if (rnd < Inoculate_pro) {
			temp = pop[ind];

			for (int taskNum = 0; taskNum < TASK_NUM; taskNum++) {
				for (int agentNum = 0; agentNum < AGENT_ALL; agentNum++) {
					if (Vaccine[taskNum][agentNum] >= 0) {
						pop[ind].encode[taskNum][agentNum] = Vaccine[taskNum][agentNum];
					}
				}
			}
			calIndiviualFitness(ind);
			if(pop[ind].weightedValue > temp.weightedValue) {
				pop[ind] = temp;
			}
		}
	}
}

void updateCurrentRepo() {
	Individual temp;
	for(int i = 0; i < P_NUM + MEM_NUM -1 ; i++) {
		for (int j = i + 1; j < P_NUM + MEM_NUM; j++) {
			if(pop[i].weightedValue > pop[j].weightedValue) {
				temp = pop[i];
				pop[i] = pop[j];
				pop[j] = temp;
			}
		}
	}
}

void calIndiviualFitness(int index) {
	double fitness[F_NUM] = {0};
	pop[index].error = 0;
	for (int taskIndex = 0; taskIndex < TASK_NUM; taskIndex++) {
		int agentStart = 0,agentEnd = 0;
		for (int process = 0; process < PROCESS_NUM; process++) {
			int agentNum = agentNumInEveryProc[process];
			agentStart = agentEnd;
			agentEnd += agentNum;
			double maxTime = 0, quality = 0, cost = 0;
			for (int agent = agentStart; agent < agentEnd; agent++) {
				if (pop[index].encode[taskIndex][agent] == 1) {
					if (agentPara[0][agent] > maxTime) {
						maxTime = agentPara[0][agent];
					}
					quality += agentPara[1][agent];
					cost += agentPara[2][agent];
					fitness[1] += 1 - agentPara[1][agent] / normalizeValue[1];
					fitness[2] += agentPara[2][agent] / normalizeValue[2];
				}
			}
			fitness[0] += maxTime / normalizeValue[0];
			if (maxTime > constraint[taskIndex][process][0]){ // 判断是否满足限制条件
				pop[index].error++;
			}
			if (quality < constraint[taskIndex][process][1]) {
				pop[index].error++;
			}
			if (cost > constraint[taskIndex][process][2]) {
				pop[index].error++;
			}
		}
	}
	double weightedValue = 0;
	for (int obj = 0; obj < F_NUM; obj++) {
		pop[index].fitness[obj] = fitness[obj];
		weightedValue += fitness[obj] * weightFactors[obj];
	}
	pop[index].weightedValue = weightedValue + pop[index].error;
}

#endif
