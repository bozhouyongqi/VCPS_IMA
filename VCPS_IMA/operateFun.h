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
	for (int agentNum = 0; agentNum < AGENT_ALL; agentNum++) {
		int sum = 0;
		for(int ind = P_NUM; ind < P_NUM + MEM_NUM; ind ++) {
			sum += pop[ind].encode[agentNum];
		}
		if (sum == MEM_NUM) {
			Vaccine[agentNum] = 1; // 
		}else if (sum == 0){
			Vaccine[agentNum] = 0;
		}else {
			Vaccine[agentNum] = -1;
		}
	}
}

void cross(){
	int i,y,*par1,*par2;
	int agentStart = 0,agentEnd = 0;
	double rnd;
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

		for (int process = 0; process < PROCESS_NUM; process++) {
			int agentNum = agentNumInEveryProc[process];
			agentStart = agentEnd;
			agentEnd += agentNum;
			rnd=(double)rand()/RAND_MAX;
			if (rnd < Cross_pro) {
				for (int agent = agentStart; agent < agentEnd; agent++) {
					temp = *(par1 + agent);
					*(par1 + agent) = *(par2 + agent);
					*(par2 + agent) = *(par1 + agent);
				}
			}
		}
	}
}

void mutate() {
	Individual *ind_ptr;
	double rnd=0;
	int *mut_ptr;
	int agentStart = 0,agentEnd = 0;
	ind_ptr = &(pop[0]);

	for (int k=0;k<P_NUM;k++)
	{
		ind_ptr=&(pop[k])	;
		mut_ptr=ind_ptr->encode;

		for (int process = 0; process < PROCESS_NUM; process++) {
			int agentNum = agentNumInEveryProc[process];
			agentStart = agentEnd;
			agentEnd += agentNum;
			rnd=(double)rand()/RAND_MAX;
			if (rnd < Mutate_pro) {
				for (int agent = agentStart; agent < agentEnd; agent++) {
					*(mut_ptr + agent) = 1 - *(mut_ptr + agent);
				}
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

			for (int agentNum = 0; agentNum < AGENT_ALL; agentNum++) {
				if (Vaccine[agentNum] >= 0) {
					pop[ind].encode[agentNum] = Vaccine[agentNum];
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
	int agentStart = 0,agentEnd = 0;
	for (int process = 0; process < PROCESS_NUM; process++) {
		int agentNum = agentNumInEveryProc[process];
		agentStart = agentEnd;
		agentEnd += agentNum;
		double maxTime = 0, quality = 0, cost = 0;
		for (int agent = agentStart; agent < agentEnd; agent++) {
			if (pop[index].encode[agent] == 1) {
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
		if (maxTime > constraint[Task_index][process][0]){ // 判断是否满足限制条件
			pop[index].error++;
		}
		if (quality < constraint[Task_index][process][1]) {
			pop[index].error++;
		}
		if (cost > constraint[Task_index][process][2]) {
			pop[index].error++;
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
