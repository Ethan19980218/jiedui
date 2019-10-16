// 结队项目.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"


#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#define LENGTH 20

int random(int a);
//char int_char(int num);
char* biaodashi(int a, int b);
char* yuefen(int a, int b);
void product_exp(int a, int b, int c, int d, int fuhao, int y, char *result);
int num;
int check();
int check1();

int main()
{
	FILE *fp;
	fp = fopen("Exercises.txt", "w+");
	fclose(fp);
	fp = fopen("Answers.txt", "w+");
	fclose(fp);
	int range = 0;

	printf("请输入产生几以内的数字：");
	scanf_s("%d", &range);
	printf("\n请输入产生多少个运算表达式：");
	scanf_s("%d", &num);


	int right1 = 0;
	int wrong1 = 0;
	char(*result)[LENGTH] = (char(*)[LENGTH])malloc(sizeof(char)*LENGTH*num);
	int i;
	for (i = 1; i <= num; i++) {
		//char expArr[2];//定义生成的题目
		int a = (int)(random(range));//分子
		int b = (int)(random(range));//分母
		int c = (int)(random(range));//另一个分子
		int d = (int)(random(range));//另一个分母
		int fuhao;//运算符
		fuhao = (int)(random(4));
		product_exp(a, b, c, d, fuhao, i, *result + i);
	}
	free(result);
	printf("\n回答完成请按回车");
	getchar();
	getchar();
	check1();
	system("pause");
	return 0;
}

void myitoa(int num_i, char *str)
{
	int j = 0, i = 0;
	char number[10] = { '0','1','2','3','4','5','6','7','8','9' };
	char temp[10] = { 0 };
	while (num_i != 0)
	{
		temp[i] = number[num_i % 10];
		i++;
		num_i = num_i / 10;
	}
	temp[i] = '\0';
	i = i - 1;
	while (i >= 0)
	{
		str[j] = temp[i];
		j++;
		i--;
	}
	str[j] = '\0';
	//printf("%s", str);
}


int random(int a) {//随机数
	int b;
	b = rand() % a + 1;
	return b;
}

void product_exp(int a, int b, int c, int d, int fuhao, int y, char *result)
{
	int fenzi;
	int fenmu;
	char*ab = biaodashi(a, b);
	char*cd = biaodashi(c, d);
	FILE *fp;
	FILE *fp1;
	fp = fopen("Exercises.txt", "a");
	fp1 = fopen("Answers.txt", "a");
	if (b != 0 && d != 0)
	{
		switch (fuhao)
		{
		case 1:
			fenzi = a * d + b * c;
			fenmu = b * d;
			fprintf(fp, "%d:%s + ", y, biaodashi(a, b));
			fprintf(fp, "%s = \n", biaodashi(c, d));
			fprintf(fp1, "%d:%s\n", y, yuefen(fenzi, fenmu));
			break;
		case 2:
			if (a*d - b * c >= 0)
			{
				fenzi = a * d - b * c;
				fenmu = b * d;
				fprintf(fp, "%d:%s - ", y, biaodashi(a, b));
				fprintf(fp, "%s = \n", biaodashi(c, d));
				fprintf(fp1, "%d:%s\n", y, yuefen(fenzi, fenmu));
			}
			else
			{
				fenzi = b * c - a * d;
				fenmu = b * d;
				fprintf(fp, "%d:%s - ", y, biaodashi(c, d));
				fprintf(fp, "%s = \n", biaodashi(a, b));
				fprintf(fp1, "%d:%s\n", y, yuefen(fenzi, fenmu));
			}
			break;
		case 3:
			fenzi = a * c;
			fenmu = b * d;
			fprintf(fp, "%d:%s × ", y, biaodashi(a, b));
			fprintf(fp, "%s = \n", biaodashi(c, d));
			fprintf(fp1, "%d:%s\n", y, yuefen(fenzi, fenmu));
			break;
		case 4:
			if (c != 0)
			{
				fenzi = a * d;
				fenmu = b * c;
				fprintf(fp, "%d:%s ÷ ", y, biaodashi(a, b));
				fprintf(fp, "%s = \n", biaodashi(c, d));
				fprintf(fp1, "%d:%s\n", y, yuefen(fenzi, fenmu));
				break;
			}
			else
				break;


		default:
			break;
		}
		fclose(fp);
		fclose(fp1);
	}
}

char* yuefen(int a, int b)
{
	static char str[10] = { 0 };
	for (int k = 0; k < 10; k++)  //for循环初始化
	{
		str[k] = 0;
	}
	int y = 1;
	char c_z[LENGTH] = { 0 };
	for (int i = a; i >= 1; i--)
	{
		if (a%i == 0 && b%i == 0)
		{
			y = i;
			break;
		}
	}
	int z = a / y;
	int m = b / y;
	if (a == 0)
	{
		str[0] = '0';
		return str;
	}
	if (m == 1)
	{
		myitoa(z, c_z);
		strcat(str, c_z);
		return str;
	}
	else
		return biaodashi(z, m);
}


char* biaodashi(int a, int b)
{
	static char str[LENGTH] = { 0 };
	for (int k = 0; k < LENGTH; k++)  //for循环初始化
	{
		str[k] = 0;
	}
	char c_a[LENGTH] = { 0 };
	char c_c[LENGTH] = { 0 };
	char c_b[LENGTH] = { 0 };
	char c_d[LENGTH] = { 0 };
	myitoa(a, c_a);          //int转为char
	myitoa(b, c_b);
	if (a >= b)
	{
		int c;
		c = a / b;
		int d;
		d = a % b;

		myitoa(c, c_c);
		myitoa(d, c_d);

		{
			if (d == 0)
			{
				strcat(str, c_c);
				return str;
			}
			strcat(str, c_c);
			strcat(str, "\'");
			strcat(str, c_d);
			strcat(str, "\/");
			strcat(str, c_b);
			return str;
		}
	}
	strcat(str, c_a);
	strcat(str, "\/");
	strcat(str, c_b);
	return str;

}
//int check() {
//	FILE *fp0;
//	fp0 = fopen("Grade.txt", "w+");
//	FILE *fp;
//	FILE *fp1;
//	int i = 0, j = 0, t = 1, w = 0, r = 0;
//	int wrongcount[LENGTH] = { 0 };
//	int rightcount[LENGTH] = { 0 };
//
//	if ((fp = fopen("Exercises.txt", "r")) == NULL) //判断文件是否存在及可读
//	{
//		printf("Exercises.txt error!");
//		return -1;
//	}
//	if ((fp1 = fopen("Answers.txt", "r")) == NULL) //判断文件是否存在及可读
//	{
//		printf("Answers.txt error!");
//		return -1;
//	}
//
//	//题目
//
//	char ch_Q = 0;
//	char ch_A = 0;
//	ch_Q = fgetc(fp);
//	while (ch_Q != EOF)
//	{
//		if (ch_Q == '=')                       //Q中浮标到=号开始判断
//		{
//			ch_Q = fgetc(fp);
//
//			while (ch_A != ':')                //A中浮标指到:号的下一位
//			{
//				ch_A = fgetc(fp1);
//				if (ch_A == EOF)
//					break;
//			}
//			while (ch_Q != '\n' && ch_A != '\n')
//			{
//				if (fgetc(fp) == fgetc(fp1))
//				{
//					ch_Q = fgetc(fp);
//					ch_A = fgetc(fp1);
//				}
//				else
//					break;
//			}
//
//			if (ch_Q == '\n' && ch_A == '\n')            //答题正确
//			{
//				rightcount[r] = t;
//				wrongcount[r] = -1;
//				r++;
//				t++;
//			}
//			else                                         //答题错误
//			{
//				wrongcount[w] = t;
//				rightcount[w] = -1;
//				w++;
//				t++;
//			}
//		}
//		else
//			ch_Q = fgetc(fp);
//	}
//	fprintf(fp0, "Correct: %d (", r);
//	for (int g = 0; g < LENGTH; g++)
//	{
//		if (rightcount[g] == -1)
//			continue;
//		else if (rightcount[g] == 0)
//			break;
//		else
//			fprintf(fp0, "%d ", rightcount[g]);
//	}
//	fprintf(fp0, ")\n");
//
//	fprintf(fp0, "Wrong: %d (", w);
//	for (int g = 0; g < LENGTH; g++)
//	{
//		if (wrongcount[g] == -1)
//			continue;
//		else if (rightcount[g] == 0)
//			break;
//		else
//			fprintf(fp0, "%d ", wrongcount[g]);
//	}
//	fprintf(fp0, ")\n");
//
//	fclose(fp0);
//	fclose(fp);
//	fclose(fp1);                     //关闭文件
//	return 0;
//}

int check1() {
	FILE *fp0;
	fp0 = fopen("Grade.txt", "w+");
	FILE *fp;
	FILE *fp1;
	int i = 0, j = 0, t = 0, w = 0, r = 0, l = 0, h = 0;
	int * rightcount = (int*)malloc((num + 2) * sizeof(int));
	memset(rightcount, -1, sizeof(rightcount));
	int * wrongcount = (int*)malloc((num + 2) * sizeof(int));
	memset(wrongcount, -1, sizeof(wrongcount));
	char StrLine[10] = {};             //每个答案最大读取的字符数
	char StrLine1[10] = {};
	if ((fp = fopen("Exercises.txt", "r")) == NULL) //判断文件是否存在及可读
	{
		printf("Exercises.txt error!");
		return -1;
	}
	if ((fp1 = fopen("Answers.txt", "r")) == NULL) //判断文件是否存在及可读
	{
		printf("Answers.txt error!");
		return -1;
	}

	char ch_Q = 0;
	char ch_A = 0;

	for (t = 1; t <= num; t++) {//一行
		ch_Q = fgetc(fp);
		if (ch_Q != EOF) {
			while (ch_Q != '\n') {//题目            
				if (ch_Q == '=') {
					ch_Q = fgetc(fp);
					for (i = 0; ch_Q != '\n'; i++) {
						ch_Q = fgetc(fp);
						StrLine[i] = ch_Q;
					}
					StrLine[i] = '\0';

					ch_A = fgetc(fp1);
					if (ch_A != EOF)
						while (ch_A != '\n') {
							if (ch_A == ':') {//答案
								for (j = 0; ch_A != '\n'; j++) {
									ch_A = fgetc(fp1);
									StrLine1[j] = ch_A;
								}
								StrLine1[j] = '\0';
							}
							else
								ch_A = fgetc(fp1);
						}
				}
				else
					ch_Q = fgetc(fp);
			}
		}
		for (int a = 0; StrLine1[a] != '\n'; a++) {
			if (StrLine[a] != StrLine1[a]) {
				w++;
				wrongcount[l] = t;//记录错的题号
				l++;
				wrongcount[l] = '\0';
				break;
			}
			else {
				if (StrLine[a + 1] == '\n' && StrLine1[a + 1] == '\n') {
					r++;
					rightcount[h] = t;  //记录对的题号
					h++;
					rightcount[h] = '\0';
					break;
				}
			}
		}


	}
	fprintf(fp0, "Correct: %d (", r);
	for (int g = 0; rightcount[g] != '\0'; g++)
		fprintf(fp0, "%d ", rightcount[g]);
	fprintf(fp0, ")\n");

	fprintf(fp0, "Wrong: %d (", w);
	for (int g = 0; wrongcount[g] != '\0'; g++)
		fprintf(fp0, "%d ", wrongcount[g]);
	fprintf(fp0, ")\n");

	fclose(fp0);
	fclose(fp);
	fclose(fp1);                     //关闭文件
	free(rightcount);
	free(wrongcount);

	return 0;
}
