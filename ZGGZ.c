#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
//#include<conio.h>
#define HEADER1 " --------------------------------------------ZGGZ------------------------------------------------- \n"
#define HEADER2 " | 编号      | 姓名      | 基本工资  | 奖金      | 扣款      | 应发工资  | 税款      | 实发工资  | \n"
#define HEADER3 " | --------- | --------- | --------- | --------- | --------- | --------- | --------- | --------- | \n"
#define END     " ------------------------------------------------------------------------------------------------- \n"
/*#define FORMAT  " |%-8s|%-10s|%8.2f|%8.2f|%8.2f|%8.2f|%8.2f|%8.2f|\n"*/
#define FORMAT  " |%-11s|%-11s|%11.2f|%11.2f|%11.2f|%11.2f|%11.2f|%11.2f|\n"
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
int Del(ZGGZ tp[],int n);
void Qur(ZGGZ tp[],int n);
void Modify(ZGGZ tp[],int n);
int Insert(ZGGZ tp[], int n);
void Count(ZGGZ tp[], int n);
void Sort(ZGGZ tp[],int n);
void Save(ZGGZ tp[],int n);
void Wrong();

int main()
{
	ZGGZ   gz[N];//60个职工
	FILE   *fp;
	int    select;
	char   choice;
	int    count=0;
	fp=fopen("db","ab+");

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
      case 2:count=Del(gz,count);break;
      case 3:Qur(gz,count);break;
      case 4:Modify(gz,count);break;
      case 5:Insert(gz,count);break;
      case 6:Count(gz,count);break;
      case 7:Sort(gz,count);break;
      case 8:Save(gz,count);break;
      case 9:Disp(gz,count);break;
      default :Wrong();break;
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
  printf("\n\n\n\n\n");
  menu();
}

void stringinput(char *t,int lens,char *notice)
{
  int n;
  while (1) {
    printf("请输入%s, 长度不超过%d:", notice, lens);
    /*gets(t);getchar();*/
    scanf("%s", t);getchar();
    n = strlen(t);
    if (n <= lens) break;
  }
/*函数用于输入字符串，并进行字符串长度验证（长度小于lens），t用于保存输入的字符串，因为是指针形式传递的，所以t相当于函数的返回值。notice用于保存printf( )中输出的提示信息。*/
}

float numberinput(char *notice)
{
  printf("请输入%s:", notice);
  float k;
  scanf("%f", &k);getchar();
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
  char choice;// = 'y';
  while (1) {
    //输入相关信息
    stringinput(tp[count].num, 10, "编号");
    if (strcmp(tp[count].num, "0") == 0) {
      menu();
      break;
    }
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
    printf("如果还有要添加，输入(y or n):\n");
    scanf("%c", &choice);getchar();
    /*choice = getchar();*/
    if(choice=='y'||choice=='Y') continue;
    printf("\n\n\n\n\n");
    menu();//添加操作完成后显示菜单供选择
    break;
  }
  return count;
  /*int add(ZGGZ TP[],int n )*/
/*函数用于在数组tp中增加工资记录元素，并返回数组中的当前记录数。*/
}

int Del(ZGGZ tp[],int n)
{
/*函数用于先在数组tp中找到满足条件的记录，然后删除该记录。*/
/*-1 delete by number,----------2 delete by name\n"*/

  if (n == 0) return -1;
  int count = n;
  int i;
  int select;
  char choice;
  int k = -1;
  while (1) {
    //输入相关信息
    printf("1）按编号删除\n2）按姓名删除\n");
    scanf("%d", &select);
    if (select == 1) {//按编号删除
      Disp(tp, count);
      stringinput(tp[count].num, 10, "编号");
      if (strcmp(tp[count].num, "0") == 0) {
        menu();
        break;
      }
      while (1) {
        if (k == 0) break;
        k = Locate(tp, count, tp[count].num, 1);
        printf("%d\n", k);
        if (k >= 0) {//找到目标，进行删除
          for (i = k; i < count; ++i) {
            tp[i] = tp[i+1];
            /*printf("i = %d\n", i);*/
          }
          k = 0;//此处k=0表示删除完成,while开始处检测是否有此标记
          continue;
        }
        printf("编号不存在，重新输入\n");
        stringinput(tp[count].num, 10, "编号");
      }
    } else if (select == 2) {//按姓名删除
      Disp(tp, count);
      stringinput(tp[count].name, 15, "姓名");
      if (strcmp(tp[count].name, "0") == 0) {
        menu();
        break;
      }
      while (1) {
        if (k == 0) break;
        k = Locate(tp, count, tp[count].name, 2);
        printf("%d\n", k);
        if (k >= 0) {//找到目标，进行删除
          for (i = k; i < count; ++i) {
            tp[i] = tp[i+1];
            printf("i = %d\n", i);
          }
          k = 0;//此处k=0表示删除完成,while开始处检测是否有此标记
          continue;
        }
        printf("姓名不存在，重新输入\n");
        stringinput(tp[count].name, 15, "姓名");
      }
    } else {//输入错误
      printf("请输入正确选项！\n");
      break;
    }
    count--;
    saveflag = 1;
    
    //如果还要删除，继续；否则退出。
    printf("如果还要删除，输入(y or n):");
    scanf("%c", &choice);getchar();
    if(choice == 'y' || choice == 'Y') continue;
    printf("\n\n\n\n\n");
    menu();//添加操作完成后显示菜单供选择
    break;
  }
  return count;//删除完成
}

void Qur(ZGGZ tp[],int n)
{
  /*函数用于在数组tp中按职工编号或者姓名查找满足条件的记录，并显示记录。1 search by number,----------2 search by name\n");*/

  if (n == 0) return;
  int count = n;
  int i;
  int select;
  char choice;
  int k = -1;
  while (1) {
    //输入相关信息
    printf("1)按编号查询\n2)按姓名查询\n3)退出\n");
    scanf("%d", &select);
    if (select == 1) {//按编号查询
      /*Disp(tp, count);*/
      stringinput(tp[count].num, 10, "编号");
      if (strcmp(tp[count].num, "0") == 0) {
        break;
      }
      k = Locate(tp, count, tp[count].num, 1);
      printf("%d\n", k);
      if (k >= 0) {//找到目标，进行查询
        for (i = 0; i < count; ++i) {
          if ( i == k) {
            printf("%s\n", HEADER2);
            printf(FORMAT, DATA);
            printf("%s\n", HEADER3);
            printf(END);
            break;
          }
        }
      } else {
        printf("编号不存在，重新输入\n");
        continue;
      }
    } else if (select == 2) {//按姓名查询
      /*Disp(tp, count);*/
      stringinput(tp[count].name, 10, "姓名");
      if (strcmp(tp[count].name, "0") == 0) {
        break;
      }
      k = Locate(tp, count, tp[count].name, 2);
      printf("%d\n", k);
      if (k >= 0) {//找到目标，进行查询
        for (i = 0; i < count; ++i) {
          if ( i == k) {
            printf("%s\n", HEADER2);
            printf(FORMAT, DATA);
            printf("%s\n", HEADER3);
            printf(END);
            break;
          }
        }
      } else {
        printf("编号不存在，重新输入\n");
        continue;
      }
    } else if (select == 3) {
      break;
    } else {//输入错误
      printf("请输入正确选项！\n");
      continue;
    }
    
    //如果还要查询，继续；否则退出。
    printf("如果还要查询，输入(y or n):");
    scanf("%c", &choice);getchar();
    if(choice == 'y' || choice == 'Y') continue;
    printf("\n\n\n\n\n");
    menu();//query操作完成后显示菜单供选择
    break;
  }
}

void Modify(ZGGZ tp[], int n)
{
  if (n == 0) return;
  int count = n;
  int k;
  char tmp_name[15];
  char tmp_num[10];
  if (count == 0) {
    return ;
  }
  Disp(tp, count);
  printf("请输入修改编号\n");
  stringinput(tp[count].num, 10, "编号");
  if (strcmp(tp[count].num, "0") == 0) {
    return ;
  }
  k = Locate(tp, count, tp[count].num, 1);
  if (k < 0) return;//未找到直接返回主菜单
  stringinput(tmp_num, 10, "新编号");
  strcpy(tp[k].num, tmp_num);
  stringinput(tmp_name, 15, "新姓名");
  strcpy(tp[k].name, tmp_name);
  tp[k].jbgz = numberinput("新基本工资");
  tp[k].jj = numberinput("新奖金");
  tp[k].kk = numberinput("新扣款");
  //完成相关计算
  tp[k].yfgz = tp[k].jbgz + tp[k].jj - tp[k].kk;
  tp[k].sk = tp[k].yfgz * 0.4;
  tp[k].sfgz = tp[k].yfgz - tp[k].sk;
  saveflag = 1;
  Disp(tp, count);
}

int Insert(ZGGZ tp[], int n)
{
  if (n == 0) return -1;
  int count = n;
  int i;
  Disp(tp,count);
  while(1){
    int k;
    stringinput(tp[count].num, 10, "编号");
    k = Locate(tp, count, tp[count].num, 1);
    if (k < 0) continue;
    for (i = count; i > k; --i) {
      tp[i] = tp[i-1];
    }
    stringinput(tp[k].num, 10, "新编号");
    stringinput(tp[k].name, 15, "新姓名");
    tp[k].jbgz = numberinput("新基本工资");
    tp[k].jj = numberinput("新奖金");
    tp[k].kk = numberinput("新扣款");
    //完成相关计算
    tp[k].yfgz = tp[k].jbgz + tp[k].jj - tp[k].kk;
    tp[k].sk = tp[k].yfgz * 0.4;
    tp[k].sfgz = tp[k].yfgz - tp[k].sk;
    count++;
    saveflag = 1;
    Disp(tp, count);
    return count;
  }
}

void Count(ZGGZ tp[], int n)
{
  int lower;
  int upper;
  int count = n;
  int cnt = 0;//统计人数
  int i;
  printf("请输入最低工资\n");
  scanf("%d", &lower);
  printf("请输入最高工资\n");
  scanf("%d", &upper);
  for ( i = 0; i < count; ++i) {
    tp[i].sfgz >= lower &&
    tp[i].sfgz <= upper &&
    cnt++;
  }
  if ( cnt > 0 ) {
    printf("搜索范围内共%d人\n", cnt);
  } else {
    printf("无符合条件人员!\n");
  }
}

void Wrong()
{
	printf("********Error,input has wrong,please input 0-9,press anykey to continue\n");
	getchar();

}

void Sort(ZGGZ tp[],int n)
{
  if (n == 0) return;
  int count = n;
  int i;
  int j;
  ZGGZ tmp;
  for (j = 0; j < count; j++) {
    for (i = j; i < count - j; ++i) {
      if (tp[i].sfgz < tp[i+1].sfgz) {
        tmp = tp[i+1];
        tp[i+1] = tp[i];
        tp[i] = tmp;
      }
    }
  }
  saveflag = 1;
}

void Save(ZGGZ tp[],int n)
{  
  int i;
  FILE *fp;
  fp = fopen("db", "wb+");
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
