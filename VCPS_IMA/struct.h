#ifndef _STRUCT_H_
#define _STRUCT_H_

typedef struct
{
	double fitness[F_NUM];
	double weightedValue; // 加权过后的目标值，即抗体亲和度
	double error;			
	int encode[AGENT_ALL];
	
}Individual;

typedef struct {
	double fitness[F_NUM];
	double weightedValue;
	double error;			
	int encode[TASK_NUM][AGENT_ALL];
}MergedIndividual;


#endif