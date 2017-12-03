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
#include "init.h"
#include "operateFun.h"
Individual pop[P_NUM + MEM_NUM];

void main() {
	
		srand((unsigned int)time(0));
		clock_t start_time,finish_time;
		double duration_time;
		int shiyan = 0,gen = 0;

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
				mutate();				// 得到种群P'
				inoculateAntibody();		// 根据适应度比较接种前和接种后的抗体
				updateCurrentRepo();		// 用记忆库与种群P'得到新种群P''，即按照fitness重新排序
				generateMemoryRepo();	// 用种群P''更新记忆库新记忆库
				generateVaccine();			// 产生疫苗
			}
		}
		cout <<"test over"<<endl;
}