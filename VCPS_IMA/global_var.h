#ifndef _G_VAR_
#define _G_VAR_

#define F_NUM 3
#define PROCESS_NUM 5
#define TASK_NUM 3
#define AGENT1_NUM 21	// 第一个环节中对应的企业的数量
#define AGENT2_NUM 18
#define AGENT3_NUM 17
#define AGENT4_NUM 16
#define AGENT5_NUM 16

#define P_NUM 200
#define MEM_NUM 10   // 记忆库大小
#define GEN_MAX 500
#define Shiyan_NUM 1
#define Cross_pro 0.7
#define Mutate_pro 0.05
#define Inoculate_pro 0.72 // 接种疫苗概率
#define AGENT_ALL AGENT1_NUM + AGENT2_NUM + AGENT3_NUM + AGENT4_NUM + AGENT5_NUM

#define MAX_PATH 256
#define PRI_MAX 5000

int agentNumInEveryProc[PROCESS_NUM] = {AGENT1_NUM, AGENT2_NUM, AGENT3_NUM, AGENT4_NUM, AGENT5_NUM};

double normalizeValue[F_NUM] = {0};
double agentPara[F_NUM][AGENT_ALL] = {0};
double weightFactors[F_NUM] = {0.38, 0.26, 0.36};
int	Vaccine[TASK_NUM][AGENT_ALL] = {-1};


// 第一个环节对应的企业在时间、质量、成本三个维度上的常数
double agent1[F_NUM][AGENT1_NUM] = {
	{7.1,7.5,6.9,6.8,7.2,7.3,6.5,7.2,7.4,7.0,6.9,7.1,7.2,6.6,6.8,6.7,7.1,7.2,6.4,6.9,6.3},
	{0.45,0.41,0.38,0.44,0.40,0.37,0.43,0.39,0.38,0.42,0.41,0.38,0.44,0.41,0.37,0.41,0.41,0.36,0.40,0.41,0.37},
	{93,90,96,92,91,94,91,92,95,93,91,93,92,91,94,92,90,93,91,90,95}
}; 
double agent2[F_NUM][AGENT2_NUM] = {
	{4.8,4.3,3.7,4.6,4.5,4.3,3.8,4.7,4.2,3.6,4.5,4.4,4.2,3.8,4.0,3.4,4.2,4.3},
	{0.41,0.46,0.39,0.40,0.45,0.38,0.39,0.44,0.37,0.41,0.44,0.36,0.41,0.43,0.37,0.41,0.45,0.38},
	{80,83,87,81,82,86,82,80,84,80,81,83,82,84,86,80,81,84}
};
double agent3[F_NUM][AGENT3_NUM] = {
	{5.3,5.5,4.5,5.1,4.9,5.2,5.4,4.4,5.0,4.8,5.2,5.3,4.3,4.8,4.9,5.1,4.8},
	{0.37,0.41,0.35,0.33,0.39,0.36,0.40,0.34,0.32,0.38,0.35,0.39,0.33,0.31,0.36,0.38,0.41},
	{59,67,63,54,60,58,65,61,52,57,56,62,63,53,61,55,57}
};
double agent4[F_NUM][AGENT4_NUM] = {
	{3.9,3.5,3.7,4.3,3.8,3.4,3.6,4.2,3.7,3.3,3.5,4.1,3.6,3.2,3.6,4.0},
	{0.44,0.35,0.38,0.39,0.43,0.34,0.37,0.38,0.42,0.33,0.36,0.37,0.41,0.32,0.36,0.38},
	{80,84,88,79,81,83,86,78,82,84,85,79,81,82,86,80}
};
double agent5[F_NUM][AGENT5_NUM] = {
	{3.1,3.9,3.3,3.7,3.5,3.0,3.8,3.2,3.6,3.4,3.2,3.6,3.1,3.5,3.3,3.4},
	{0.25,0.28,0.35,0.31,0.30,0.24,0.27,0.34,0.30,0.28,0.26,0.32,0.33,0.31,0.28,0.26},
	{74,77,82,79,83,73,76,81,80,82,72,76,83,81,82,79}
};

double constraint[TASK_NUM][PROCESS_NUM][F_NUM] = {
	8.0, 0.4, 800,
	5.3, 0.35, 750,
	5.4, 0.34, 650,
	4.3, 0.35, 780,
	4.5, 0.32, 750,

	8.9, 0.41, 810,
	5.2, 0.44, 760,
	9.0, 0.32, 640,
	4.5, 0.38, 770,
	4.0, 0.35, 740,

	8.2, 0.39, 820,
	7.0, 0.42, 760,
	6.5, 0.34, 630,
	7.9, 0.36, 790,
	8.0, 0.32, 760
};

FILE *time_matrix;
FILE *Elite_Archive;						//精英档案

FILE *last_gen_ptr;
FILE *to_CompareMine;
FILE *weightValueFile;

#endif