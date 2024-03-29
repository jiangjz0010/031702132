#include <iostream>
#include <cstring>
#include <stdio.h>
#include <string>
#include <iomanip>
#include <stdlib.h>
using namespace std;
int a[10][10];//用来存储数独
int n; //所求的棋面数
int m;//数独的阶数
int sign = 0;//成功标记
FILE* fp1;
FILE* fp2;
bool judge_row_col(int x, int key)/*判断数独的每一列每一行是否重复*/
{
	int row = x / m;
	int col = x % m;
	for (int i = 0; i < m; i++)/*判断行 */
	{
		if (a[row][i] == key)
		{
			return false;
		}
	}
	for (int i = 0; i < m; i++)/*判断列*/
	{
		if (a[i][col] == key)
		{
			return false;
		}
	}
	return true;
}
void print()/*把求解完的数独写入txt*/
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			fprintf(fp2, "%d", a[i][j]);/*写入txt*/
			if (j < m - 1)
			{
				fprintf(fp2, " ");
			}
		}
		fprintf(fp2, "\n");
	}
}

void DFS(int x)/* 深搜构造数独 */
{
	if (sign)/*如果已经完成 直接返回*/
	{
		return;
	}
	if (x == m * m)/* 说明所有的都符合，数独求解完毕，退出递归 */
	{
		print();
		sign = 1;
		return;
	}
	int row = x / m;
	int col = x % m;
	if (a[row][col] != 0)/*当前位不为空时跳过*/
	{
		DFS(x + 1);
	}
	else  /* 否则对当前位进行枚举测试 */
	{
		for (int i = 1; i <= m; i++)
		{
			if (judge_row_col(x, i))
			{
				a[row][col] = i;/* 继续搜索 */
				DFS(x + 1);/* 返回时如果构造成功，则直接退出 */
				a[row][col] = 0; 
			}
		}
	}
}
int main(int argc, char* argv[])/*将答案按照要求输出*/
{

	m = atoi(argv[2]);/*数独阶数*/
	n = atoi(argv[4]);/*待求解的数独面数*/
	char* inputfile = argv[6];/*输入的文件名：比如m3n5.txt*/
	char* outputfile = argv[8];/*输出的文件名：比如outm3n5.txt*/
	fp1 = fopen(inputfile, "r");/*打开输入文件*/
	if (fp1 == NULL)/*如果文件不存在，返回错误*/
	{
		return -1;
	}
	fp2 = fopen(outputfile, "w");/*打开输出文件*/
	if (fp2 == NULL) /*如果文件不存在，返回错误*/
	{
		return -1;
	}
	fclose(fp2);
	while (n--)/*依次读取输入文件中的数独*/
	{
		int i, j;
		memset(a, 0, sizeof(a));
		sign = 0;
		for (i = 0; i < m; i++)
		{
			for (j = 0; j < m; j++)
			{
				fscanf(fp1, "%d", &a[i][j]);/*读取数独*/
			}
		}
		fp2 = fopen(outputfile, "a");/*打开输出文件*/
		DFS(0);
		if (n > 0)
		{
			fprintf(fp2, "\n");/*写入输出至文件*/

		}
		fclose(fp2);/*关闭输出文件*/
	}
	fclose(fp1);/*关闭输入文件*/
	return 0;
}