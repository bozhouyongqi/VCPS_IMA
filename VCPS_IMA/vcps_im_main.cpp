/************************************************************************/
/* author: 王永奇
 * date  : 2017/11/30
 * title : 基于人工免疫算法的虚拟企业伙伴选择算法
/************************************************************************/
#include<iostream>
#include<time.h>
#include<math.h>
#include <fstream>
#include <direct.h>
using namespace std;

#include <string>
#include <stdlib.h>
#include <time.h>

#include "global_var.h"
#include "struct.h"

Individual pop[P_NUM + MEM_NUM];

#include "init.h"
#include "operateFun.h"

void print_last_gen(int run_num,double cost_time);
void main() {
		srand((unsigned int)time(0));
		clock_t start_time,finish_time;
		double duration_time;
		int shiyan = 0,gen = 0;
		fstream ofz;
		ofz.open("each_run_time_my.txt");

		for (shiyan = 0; shiyan < Shiyan_NUM; shiyan++) {
			start_time=clock();
			init();
			for (int i = 0; i < P_NUM; i++) {
				calIndiviualFitness(i); // 逐个个体计算适应度
			}
			generateMemoryRepo();	// 生成记忆库
			generateVaccine();		// 产生疫苗
			
			for (gen = 0; gen < GEN_MAX; gen++) {
				cross();
				mutate();					// 得到种群P'
				inoculateAntibody();		// 根据适应度比较接种前和接种后的抗体
				updateCurrentRepo();		// 用记忆库与种群P'得到新种群P''，即按照fitness重新排序
				generateMemoryRepo();		// 用种群P''更新记忆库新记忆库
				generateVaccine();			// 产生疫苗
				if (gen == GEN_MAX -1) {
					finish_time = clock();
					duration_time = (double)(finish_time -start_time)/ CLOCKS_PER_SEC;
					cout<<duration_time<<" s"<<endl;
					print_last_gen(shiyan, duration_time);

					ofz<<duration_time<<endl;
				}
				if(0==gen%100)
					cout<<"gen="<<gen<<endl	 ;
			}
		}
		cout <<"test over"<<endl;
}


void print_last_gen(int run_num,double cost_time)
{
	char num[100];
	itoa(run_num,num,10);

	char buffer[MAX_PATH];
	getcwd(buffer,MAX_PATH);//返回当前工作环境的文件目录存放在buffer中

	char file1[500];
	sprintf(file1,"%s\\last_generation",buffer);//将buffer中的当前文件目录写到file1中，并创建一个新的文件命名为fitness
	sprintf(file1,"%s\\last_generation%s.txt",file1,num);//在file1中写上每次迭代产生的不同fitness文件的路径
	last_gen_ptr=fopen(file1,"wt"); 

	char file2[500];
	sprintf(file2,"%s\\to_CompareMine",buffer);
	sprintf(file2,"%s\\to_CompareMine%s.txt",file2,num);
	to_CompareMine=fopen(file2,"wt"); 

	char file3[500];
	sprintf(file3,"%s\\weightedValue",buffer);
	sprintf(file3,"%s\\weightedValue%s.txt",file3,num);
	weightValueFile=fopen(file3,"wt"); 

	int f=0,l=0,m=0,n=0;
	int best_num=0;
	Individual *ind_ptr;
	for(f=P_NUM;f < P_NUM + MEM_NUM;f++)
	{
		ind_ptr=&(pop[f]);
		if(ind_ptr->error < 1e-7) {
			best_num++;
			fprintf(last_gen_ptr, "%s", "individual: ");
			fprintf(last_gen_ptr,"%d\n",f);
			fprintf(last_gen_ptr,"%s","encode:\n");
			for(l=0;l<TASK_NUM;l++)
			{
				for(m=0;m<AGENT_ALL;m++)
				{
					fprintf(last_gen_ptr,"%d",ind_ptr->encode[l][m]);
					fprintf(last_gen_ptr,"%s","  ");
				}
				fprintf(last_gen_ptr,"%s","\n");
			}
			fprintf(last_gen_ptr,"%s","\n");

			fprintf(last_gen_ptr,"%s","\n");
			fprintf(last_gen_ptr,"%s","\n");
			fprintf(last_gen_ptr,"%s","总时间= ");
			fprintf(last_gen_ptr,"%f",ind_ptr->fitness[0]);
			fprintf(last_gen_ptr,"%s","   ");	

			fprintf(last_gen_ptr,"%s","质量(1-q)=");
			fprintf(last_gen_ptr,"%f,",ind_ptr->fitness[1]);

			fprintf(last_gen_ptr,"%s","总花费成本=");
			fprintf(last_gen_ptr,"%f,",ind_ptr->fitness[2]);

			fprintf(last_gen_ptr,"%s","   ");	
			fprintf(last_gen_ptr,"%s","error:  ");
			fprintf(last_gen_ptr,"%d",ind_ptr->error);

			fprintf(last_gen_ptr,"%s","   ");	
			fprintf(last_gen_ptr,"%s","加权后的适应度:  ");
			fprintf(last_gen_ptr,"%f",ind_ptr->weightedValue);

			fprintf(last_gen_ptr,"%s","\n");
			for(l=0;l<F_NUM;l++){
				fprintf(to_CompareMine,"%f ",ind_ptr->fitness[l]);
			}
			fprintf(to_CompareMine,"%s","\n");
			fprintf(weightValueFile,"%f\n", ind_ptr->weightedValue);
		} 
	}  //for(f) end;
	fprintf(last_gen_ptr,"%s","优胜解数量: ");
	fprintf(last_gen_ptr,"%d  ",best_num);

	fprintf(last_gen_ptr,"%s","运行时间: ");
	fprintf(last_gen_ptr,"%f",cost_time);

	fclose(last_gen_ptr);
	fclose(to_CompareMine);
}