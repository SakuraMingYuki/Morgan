#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define L 10
#define LN 128

int menu();
int select();
void add();
void QueSelect();
void ChangeQue();
void AnsCheck();
void PrintfQue(int nq, int n);
void save();
void read();


typedef struct 
{
	char question[LN], A[L], B[L], C[L], D[L], answer[L], cans[L];
}Test;

Test q[LN];
int a[LN];
int numq = 0, numa = 0;

int main()
{
	int i;
	char passnum[L] = { "123456" }, pass[L];
	printf("欢迎使用单项选择题标准考试化系统\n");
	printf("请输入您的密码:\n");
	for (i = 1; i <= 3; i++)
	{
		scanf("%s", pass);
		if (!strcmp(passnum, pass))
		{
			printf("密码正确\n");
			system("pause...");
			menu();
		}
		else
		{
			if (i == 3)
				printf("错误次数过多！请重新打开系统！\n");
			else
				printf("密码错误！请重新输入！\n");
		}
	}
	return 0;
}

int menu()
{
	while (1)
	{
		switch (select())
		{
		case 1:
			add();
			break;
		case 2:
			ChangeQue();
			break;
		case 3:
			QueSelect();
			break;
		case 4:
			AnsCheck();
			break;
		case 5:
			save();
			break;
		case 6:
			read();
			break;
		case 7:
			exit(1);
		}
	}
}

int select()
{
	int n;
	system("cls");
	printf("主菜单\n");
	printf("1.试题添加\n");
	printf("2.更改试题\n");
	printf("3.试题抽取与答题\n");
	printf("4.判卷出成绩\n");
	printf("5.文件保存\n");
	printf("6.文件导入\n");
	printf("7.退出系统\n");
	do
	{
		printf("请选择您的操作：");
		scanf("%d", &n);
	} while (n < 0 || n > 7);
	return (n);
}

void add()
{
	int i, j;
	system("cls");
	printf("请输入想要输入的题目个数：");
	scanf("%d", &j);
	if (j <= 0 || j > LN)
	{
		printf("错误！请重新选择！\n");
		system("pause...");
	}
	else
	{
		i = numq;
		j = j + numq;
		for (i; i < j; i++)
		{
			printf("请输入第%d道题题目、题干和选项:\n", i + 1);
			printf("请输入题目:");
			scanf("%s", &q[i].question);
			printf("请输入选项A:");
			scanf("%s", &q[i].A);
			printf("请输入选项B:");
			scanf("%s", &q[i].B);
			printf("请输入选项C:");
			scanf("%s", &q[i].C);
			printf("请输入选项D:");
			scanf("%s", &q[i].D);
			printf("请输入答案:");
			scanf("%s", &q[i].answer);
			getchar();
			system("cls");
			numq++;
		}
		printf("添加完成！\n");
		system("pause...");
	}
}

void QueSelect()
{
	int S, i;
	system("cls");
	printf("请输入抽取题数:\n");
	scanf("%d", &S);
	system("cls");
	if (S <= numq && S > 0)
	{
		numa = 0;
		for (i = 0; i < S; i++)
		{
			int Num = rand() % numq;
			PrintfQue(Num, i);
			getchar();
			printf("\n请输入你的答案:\n");
			scanf("%s", &q[i].cans);
			a[i] = Num;
			numa++;
			system("cls");
		}
		printf("考试结束，");
		system("pause...");
	}
	else
	{
		printf("错误！请重新选择！\n");
		system("pause...");
	}
}

void PrintfQue(int nq, int n)
{
	printf("%d:", n + 1);
	printf("%s\n", q[nq].question);
	printf("%s\n", q[nq].A);
	printf("%s\n", q[nq].B);
	printf("%s\n", q[nq].C);
	printf("%s\n", q[nq].D);
}


void ChangeQue()
{
	int c;
	system("cls");
	printf("请输入需要更改的题号：");
	scanf("%d", &c);
	if (c <= 0 || c > numq)
	{
		printf("错误！请重新选择！\n");
		system("pause...");
	}
	else
	{
		c = c - 1;
		getchar();
		printf("请输入题目:");
		scanf("%s", &q[c].question);
		printf("请输入选项A:");
		scanf("%s", &q[c].A);
		printf("请输入选项B:");
		scanf("%s", &q[c].B);
		printf("请输入选项C:");
		scanf("%s", &q[c].C);
		printf("请输入选项D:");
		scanf("%s", &q[c].D);
		printf("请输入答案:");
		scanf("%s", &q[c].answer);
		getchar();
		system("cls");
		printf("更改完成！\n");
		system("pause...");
	}
}

void AnsCheck()
{
	int i, grade = 0;
	system("cls");
	for (i = 0; i < numa; i++)
	{
		printf("%d:", i + 1);
		printf("%s\n", q[a[i]].question);
		printf("%s\n", q[a[i]].A);
		printf("%s\n", q[a[i]].B);
		printf("%s\n", q[a[i]].C);
		printf("%s\n", q[a[i]].D);
		printf("你的答案是:%s	", q[i].cans);
		printf("正确答案是:%s	", q[a[i]].answer);
		if (!strcmp(q[i].cans, q[a[i]].answer))
		{
			printf("true\n");
			grade = grade + 100 / numa;
		}
		else
		{
			printf("false\n");
		}
	}
	printf("本次考试你的成绩为: %d\n", grade);
	system("pause...");
}

void save()
{
	system("cls");
	FILE* fp;
	int i = 0;
	char filename[50];
	printf("请输入导出文件夹，列如:D:\\1.txt\n");
	scanf("%s", filename);
	if ((fp = fopen(filename, "w")) == NULL)
	{
		printf("文件保存失败!\n");
		system("pause...");
		exit(1);
	}
	while (i < numq)
	{
		fwrite(&q[i], sizeof(Test), 1, fp);
		i++;
	}
	fclose(fp);
	printf("记录已保存到文件中\n");
	system("pause...");
}

void read()
{
	system("cls");
	int i;
	FILE* fp;
	char filename[20];
	printf("请输入你要导入的文件名及路径:");
	scanf("%s", filename);
	if ((fp = fopen(filename, "r")) == NULL)
	{
		printf("文件打开失败!\n");
		system("pause...");
		exit(1);
	}
	i = 0;
	while (!feof(fp))
	{
		if (1 != fread(&q[i], sizeof(Test), 1, fp))
			break;
		i++;
	}
	fclose(fp);
	printf("已经成功从文件%s导入数据!\n", filename);
	system("pause...");
	numq = i;
}
