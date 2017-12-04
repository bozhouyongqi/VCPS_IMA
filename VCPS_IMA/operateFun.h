#ifndef _OPERATE_FUN_H
#define _OPERATE_FUN_H


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
}

void generateVaccine(){

}

void cross(){

}

void mutate() {

}	

void inoculateAntibody() {

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
