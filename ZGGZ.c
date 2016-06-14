#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<conio.h>
#define HEADER1 " --------------------------------------------ZGGZ------------------------------------------------- \n"
#define HEADER2 " | 编号      | 姓名      | 基本工资  | 奖金      | 扣款      | 应发工资  | 税款      | 实发工资  | \n"
#define HEADER3 " | --------- | --------- | --------- | --------- | --------- | --------- | --------- | --------- | \n"
#define END     " ------------------------------------------------------------------------------------------------- \n"
#define FORMAT  "|%-8s|%-10s|%8.2f|%8.2f|%8.2f|%8.2f|%8.2f|%8.2f|"
#define DATA tp[i].num,tp[i].name,tp[i].jbgz,tp[i].jj,tp[i].kk,tp[i].yfgz,tp[i].sk,tp[i].sfgz
#define DATA1 tp[p].num,tp[p].name,tp[p].jbgz,tp[p].jj,tp[p].kk,tp[p].yfgz,tp[p].sk,tp[p].sfgz
#define N 60
int  saveflag=0;

typedef struct employee
{
	char num[10]; // 职工编号
	char name[15];// 职工姓名.
	float jbgz;//基本工资
	float jj;//奖金
	float kk;//扣款
	float yfgz;//应发工资
	float sk;//扣税
	float sfgz;//实发工资
}ZGGZ;

void menu();
void Disp(ZGGZ tp[],int n);
void stringinput(char *t,int lens,char *notice);
float numberinput(char *notice);
int Locate(ZGGZ tp[],int n,char findmess[],int select);
int Add(ZGGZ tp[],int n);
void Save(ZGGZ tp[],int n);

int main()
{
	ZGGZ   gz[N];//60个职工
	FILE   *fp;
	int    select;
	char   choice;
	int    count=0;
	fp=fopen("zggz","ab+");

  //判断文件是否打开成功
	if(fp==NULL) {
		printf("\n----------cannot open file");
		exit(0);
	}

	while(!feof(fp)) {
		if(fread( &gz[count], sizeof(ZGGZ),1,fp )==1)
			count++;
	}

	fclose(fp);
	menu();
	while(1) {
    printf("please enter your choice(0-9)\n");
    scanf("%d",&select);
    if(select==0) {
      if(saveflag==1) {
        printf("file has changed,do you save it?(y/n)");
        getchar();
        scanf("%c",&choice);
        if(choice=='y'||choice=='Y') {
          Save(gz,count);
          printf("thank you for your useness\n");
        } else
          printf("thank you for your useness\n");
        break;
      } else {
        printf("thank you for your useness\n");
        break;
      }
    }
    switch(select)
    {
      case 1:count=Add(gz,count);break;
      /*case 2:count=Del(gz,count);break;*/
      /*case 3:Qur(gz,count);break;*/
      /*case 4:Modify();break;*/
      /*case 5:Insert();break;*/
      /*case 6:Count();break;*/
      /*case 7:Sort();break;*/
      case 8:Save(gz,count);break;
      case 9:Disp(gz,count);break;
      /*default :Wrong();break;*/
    }
  }
  return 0;
}

void menu()
{
  printf("                EMPLOYEE  SYSTEM             \n\n");
	printf("   * 1 input   record       *  2 delete record \n");
	printf("   * 3 search  record       *  4 modify record \n");
	printf("   * 5 insert  record       *  6 count  record \n");
	printf("   * 7 sort    record       *  8 save   record \n");
	printf("   * 9 display record       *  0 quit   system \n");
}

void Disp(ZGGZ tp[],int n)
{
/*函数用于显示数组中存储的n条记录，内容为emplyee中的内容。*/
  int i;
  printf("%s\n", HEADER1);
  printf("%s\n", HEADER2);
  printf("%s\n", HEADER3);
  for (i = 0; i < n; ++i) {
    printf(FORMAT, DATA);
    printf("%s\n", HEADER3);
  }
  printf(END);

}

void stringinput(char *t,int lens,char *notice)
{
  int n;
  while (1) {
    printf("请输入%s, 长度不超过%d:", notice, lens);
    /*gets(t);getchar();*/
    scanf("%s", t);
    n = strlen(t);
    if (n <= lens) break;
  }
/*函数用于输入字符串，并进行字符串长度验证（长度小于lens），t用于保存输入的字符串，因为是指针形式传递的，所以t相当于函数的返回值。notice用于保存printf( )中输出的提示信息。*/
}

float numberinput(char *notice)
{
  printf("请输入%s:", notice);
  float k;
  scanf("%f", &k);
/*函数用于输入数值型数据，notice用于保存printf( )中输出的提示信息。该函数返回用户输入的浮点类型数据值（不小于0）。*/
  return k;
}

int Locate(ZGGZ tp[],int n,char findmess[],int select)
{
  int i;
  if (select == 1){
    for (i = 0; i < n; ++i) {
      if (strcmp(tp[i].num,findmess) == 0) {//按工号查找
        return i;
      }
    }
    return -1;
  } else if (select == 2) {
    for (i = 0; i < n; ++i) {
      if (strcmp(tp[i].name,findmess) == 0) {//按名字查找
        return i;
      }
    }
    return -1;
  } else {
    printf("error\n");
    return -2;//-2代表写错了
  }
/*函数用于定位数组中符合要求的元素，并返回该数组元素的下标值。
 * 参数findmess[]保存要查找的内容.。select=1,按num查找；
 * select=2,按name查找。成功，返回下标；失败返回-1。*/
}

int Add(ZGGZ tp[],int n)
{
  int count = n;
  char choice;
  while (1) {
    //输入相关信息
    stringinput(tp[count].num, 10, "编号");
    if (strcmp(tp[count].num, "0") == 0) break;
    while (1) {
      int k;
      k = Locate(tp, count, tp[count].num, 1);
      if (k < 0) break;
      printf("编号已存在，重新输入\n");
      stringinput(tp[count].num, 10, "编号");
    }
    stringinput(tp[count].name, 15, "姓名");
    tp[count].jbgz = numberinput("基本工资");
    tp[count].jj = numberinput("奖金");
    tp[count].kk = numberinput("扣款");
    //完成相关计算，count++
    tp[count].yfgz = tp[count].jbgz + tp[count].jj - tp[count].kk;
    tp[count].sk = tp[count].yfgz * 0.4;
    tp[count].sfgz = tp[count].yfgz - tp[count].sk;
    count++;
    saveflag = 1;
    //如果还有要添加，继续；否则退出。
    printf("如果还有要添加，输入（y or n）：");
    scanf("%c", &choice);getchar();
    /*choice = getchar();*/
    if(choice == 'y' || choice == 'Y') continue;
    break;
  }
  return count;
  /*int add(ZGGZ TP[],int n )*/
/*[>函数用于在数组tp中增加工资记录元素，并返回数组中的当前记录数。<]*/
}

void Save(ZGGZ tp[],int n)
{  
  int i;
  FILE *fp;
  fp = fopen("zggz", "wb+");
  if (fp == NULL) {
    printf("\n-----------------cannot open file");
    exit(0);
  }
  for (i = 0; i < n; ++i) {
    fwrite( &tp[i], sizeof(ZGGZ),1,fp );
  }
  fclose(fp);
  //修改完毕，saveflag归零
  saveflag = 0;
}
