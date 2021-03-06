#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;
vector<int> tree[201]; //能级转移矩阵，一个201维向量，因为PAT，在学STL，因此尝试用之模拟邻接矩阵的意思
int energy[201];	   //有的能级
int photon[201];	   //光子能量
int state[201][2];	   //dp状态转移矩阵，【0】可以用于判断是否访问过和暂存解，【1】用于记录每一步最优解
/*测试用例：5 2 1 3 5 8 11 2 3*/
void DFS(int i, int flag)
{
	state[i][0] = 0; //用于判断访问状态和暂存解，0是访问过了
	state[i][1] = energy[i];//用于记录每步最优解
	for (int j = 0; j < tree[i].size(); j++)//寻找这一原子的所有可以转移状态
	{
		int temp = tree[i][j];
		if (temp == flag)//不和自己整
		{
			continue;
		}
		DFS(temp, i);//先一直寻到最底层，然后一层一层往上转移
		/*每一波dfs找到一条连续变换的通路，然后一层中左面存放下层的最优解，右面存放
		  下一层经过这一层操作之后的最优解，然后两种状态比较大的转移到上一层的左面*/
		state[i][0] += max(state[temp][0], state[temp][1]);
		state[i][1] += state[temp][0];
	}
}
int main()
{
	int n, m;
	while (scanf("%d%d", &n, &m))
	{
		/*处理输入内容*/
		if (n == 0 && m == 0)
		{
			system("pause");
			return 0;
		}
		for (int i = 0; i < n; i++)
		{
			scanf("%d", &energy[i]);
		}
		for (int i = 0; i < m; i++)
		{
			scanf("%d", &photon[i]);
		}
		memset(state, -1, sizeof(state));
		for (int i = 0; i < n; i++)
		{
			tree[i].clear();//清空每一个vector的状态
		}
		/*找到所有可以互相转化的能级，构成能级矩阵tree*/
		for (int i = 0; i < n; i++)
		{
			for (int j = i + 1; j < n; j++)
			{
				for (int k = 0; k < m; k++)
				{
					if ((energy[j] - energy[i]) == photon[k])//光子能量可以使这俩互相转换
					{
						tree[i].push_back(j);//用201维向量模拟类似邻接矩阵，另：本想使用map键值对的，
						tree[j].push_back(i);//但是map提供的方法坑了，也没有自己写一个方法，故放弃。
					}
				}
			}
		}
		/*dp开始*/
		int sum = 0;
		for (int i = 0; i < n; i++)//有可能现有的原子不是所有状态能连续变换，分成两部分
		{
			if (state[i][0] == -1)
			{
				DFS(i, 0);
				sum += max(state[i][0], state[i][1]);//每层转移，第一层状态的转移就是最后的答案
			}
		}
		cout << sum << endl;
	}
	system("pause");
	return 0;
}