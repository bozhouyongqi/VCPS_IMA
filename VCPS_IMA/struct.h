#ifndef _STRUCT_H_
#define _STRUCT_H_

typedef struct
{
	double fitness[F_NUM];
	double weightedValue; // ��Ȩ�����Ŀ��ֵ���������׺Ͷ�
	double error;			
	int encode[AGENT_ALL];
	
}Individual;


#endif