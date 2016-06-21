#include <stdio.h>
/*void stringinput(char *t,int lens,char *notice)*/
/*{*/
/*函数用于输入字符串，并进行字符串长度验证（长度小于lens），t用于保存输入的字符串，因为是指针形式传递的，所以t相当于函数的返回值。notice用于保存printf( )中输出的提示信息。*/

/*}*/

/*float numberinput(char *notice)*/
/*{*/
/*函数用于输入数值型数据，notice用于保存printf( )中输出的提示信息。该函数返回用户输入的浮点类型数据值（不小于0）。*/
/*}*/

/*void Disp(ZGGZ tp[],int n)*/
/*{*/
/*函数用于显示数组中存储的n条记录，内容为emplyee中的内容。*/

/*}*/

/*int Locate(ZGGZ tp[],int n,char findmess[],int select)*/
/*{*/
/*函数用于定位数组中符合要求的元素，并返回该数组元素的下标值。参数findmess[]保存要查找的内容.。select=1,按num查找；select=2,按name查找。成功，返回下标；失败返回-1。*/
/*}*/

/*int Add(ZGGZ tp[],int n)*/
/*{*/
	/*int add(ZGGZ TP[],int n )*/
/*函数用于在数组tp中增加工资记录元素，并返回数组中的当前记录数。*/

/*}*/

/*int Del(ZGGZ tp[],int n)*/
/*{*/
/*[>函数用于先在数组tp中找到满足条件的记录，然后删除该记录。<]*/
/*[>-1 delete by number,----------2 delete by name\n"<]*/


/*}*/

/*Qur(ZGGZ tp[],int n)*/
/*{*/
/*[>函数用于在数组tp中按职工编号或者姓名查找满足条件的记录，并显示记录。1 search by number,----------2 search by name\n");<]*/

/*}*/

/*void Modify()*/
/*{*/
  /*printf("this is modify");*/
/*}*/

/*void Insert()*/
/*{*/
  /*printf("this is insert");*/
/*}*/

/*void Count()*/
/*{*/
  /*printf("this is count");*/
/*}*/

/*void Sort()*/
/*{*/
  /*printf("this is sort");*/
/*}*/

/*void Save(ZGGZ tp[],int n)*/
/*{  */
	
/*}*/


/*void Wrong()*/
/*{*/
	/*printf("********Error,input has wrong,please input 0-9,press anykey to continue\n");*/
	/*getchar();*/
/*}*/

/*int main()*/
/*{*/
	/*ZGGZ gz[N];*/
	/*FILE *fp;*/
	/*int select;*/
	/*char choice;*/
	/*int count=0;*/
	/*fp=fopen("zggz","ab+");*/

	/*if(fp==NULL) {*/
		/*printf("\n----------cannot open file");*/
		/*exit(0);*/
	/*}*/

	/*while(!feof(fp)) {*/
		/*if(fread(&gz[count],sizeof(ZGGZ),1,fp)==1)*/
			/*count++;*/
	/*}*/

	/*fclose(fp);*/
	/*menu();*/
	/*while(1) {*/
    /*printf("please enter your choice(0-9)\n");*/
    /*scanf("%d",&select);*/
    /*if(select==0) {*/
      /*if(saveflag==1) {*/
        /*printf("file has changed,do you save it?(y/n)");*/
        /*getchar();*/
        /*scanf("%c",&choice);*/
        /*if(choice=='y'||choice=='Y') {*/
          /*Save(gz,count);*/
          /*printf("thank you for your useness");*/
        /*} else*/
          /*printf("thank you for your useness");*/
        /*break;*/
      /*} else {*/
        /*printf("thank you for your useness");*/
        /*break;*/
      /*}*/
    /*}*/
    /*switch(select)*/
    /*{*/
      /*case 1:count=Add(gz,count);break;*/
      /*case 2:count=Del(gz,count);break;*/
      /*case 3:Qur(gz,count);break;*/
      /*case 4:Modify();break;*/
      /*case 5:Insert();break;*/
      /*case 6:Count();break;*/
      /*case 7:Sort();break;*/
      /*case 8:Save(gz,count);break;*/
      /*case 9:Disp(gz,count);break;*/
      /*default :Wrong();break;*/
    /*}*/
  /*}*/
  /*return 0;*/
/*}*/
