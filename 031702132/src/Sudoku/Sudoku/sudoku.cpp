#include <iostream>
#include <cstring>
#include <stdio.h>
#include <string>
#include <iomanip>
#include <stdlib.h>
using namespace std;
int a[10][10];//�����洢����
int n; //�����������
int m;//�����Ľ���
int sign = 0;//�ɹ����
FILE* fp1;
FILE* fp2;
bool judge_row_col(int x, int key)/*�ж�������ÿһ��ÿһ���Ƿ��ظ�*/
{
	int row = x / m;
	int col = x % m;
	for (int i = 0; i < m; i++)/*�ж��� */
	{
		if (a[row][i] == key)
		{
			return false;
		}
	}
	for (int i = 0; i < m; i++)/*�ж���*/
	{
		if (a[i][col] == key)
		{
			return false;
		}
	}
	return true;
}
void print()/*������������д��txt*/
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			fprintf(fp2, "%d", a[i][j]);/*д��txt*/
			if (j < m - 1)
			{
				fprintf(fp2, " ");
			}
		}
		fprintf(fp2, "\n");
	}
}

void DFS(int x)/* ���ѹ������� */
{
	if (sign)/*����Ѿ���� ֱ�ӷ���*/
	{
		return;
	}
	if (x == m * m)/* ˵�����еĶ����ϣ����������ϣ��˳��ݹ� */
	{
		print();
		sign = 1;
		return;
	}
	int row = x / m;
	int col = x % m;
	if (a[row][col] != 0)/*��ǰλ��Ϊ��ʱ����*/
	{
		DFS(x + 1);
	}
	else  /* ����Ե�ǰλ����ö�ٲ��� */
	{
		for (int i = 1; i <= m; i++)
		{
			if (judge_row_col(x, i))
			{
				a[row][col] = i;/* �������� */
				DFS(x + 1);/* ����ʱ�������ɹ�����ֱ���˳� */
				a[row][col] = 0; 
			}
		}
	}
}
int main(int argc, char* argv[])/*���𰸰���Ҫ�����*/
{

	m = atoi(argv[2]);/*��������*/
	n = atoi(argv[4]);/*��������������*/
	char* inputfile = argv[6];/*������ļ���������m3n5.txt*/
	char* outputfile = argv[8];/*������ļ���������outm3n5.txt*/
	fp1 = fopen(inputfile, "r");/*�������ļ�*/
	if (fp1 == NULL)/*����ļ������ڣ����ش���*/
	{
		return -1;
	}
	fp2 = fopen(outputfile, "w");/*������ļ�*/
	if (fp2 == NULL) /*����ļ������ڣ����ش���*/
	{
		return -1;
	}
	fclose(fp2);
	while (n--)/*���ζ�ȡ�����ļ��е�����*/
	{
		int i, j;
		memset(a, 0, sizeof(a));
		sign = 0;
		for (i = 0; i < m; i++)
		{
			for (j = 0; j < m; j++)
			{
				fscanf(fp1, "%d", &a[i][j]);/*��ȡ����*/
			}
		}
		fp2 = fopen(outputfile, "a");/*������ļ�*/
		DFS(0);
		if (n > 0)
		{
			fprintf(fp2, "\n");/*д��������ļ�*/

		}
		fclose(fp2);/*�ر�����ļ�*/
	}
	fclose(fp1);/*�ر������ļ�*/
	return 0;
}