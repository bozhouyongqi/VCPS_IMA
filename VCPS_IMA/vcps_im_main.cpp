/************************************************************************/
/* author: ������
 * date  : 2017/11/30
 * title : �����˹������㷨��������ҵ���ѡ���㷨
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
				calIndiviualFitness(i); // ������������Ӧ��
			}
			generateMemoryRepo();	// ���ɼ����
			generateVaccine();		// ��������
			
			for (gen = 0; gen < GEN_MAX; gen++) {
				cross();
				mutate();				// �õ���ȺP'
				inoculateAntibody();		// ������Ӧ�ȱȽϽ���ǰ�ͽ��ֺ�Ŀ���
				updateCurrentRepo();		// �ü��������ȺP'�õ�����ȺP''��������fitness��������
				generateMemoryRepo();	// ����ȺP''���¼�����¼����
				generateVaccine();			// ��������
			}
		}
		cout <<"test over"<<endl;
}