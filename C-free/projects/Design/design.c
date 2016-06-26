#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#define file "temp.txt"

struct user
{
    int id;
    char name[20];
    char password[6];
    double money;
};

void add()
{
    printf("%30s\n","***用户开户***");
    printf("---------------------------------------------\n\n");

    struct user getuser();
    int count();

    FILE *fp;
    int number;
    struct user temp;

    if((fp=fopen(file,"ab"))==NULL)
    {
        printf("cannot open file!\n");
        exit(1);
    }

    temp=getuser();
    number=count();
    temp.id=number+1;

    fwrite(&temp,sizeof(struct user),1,fp);

    printf("用户开户成功!\n");

    fclose(fp);
}
int count()
{
    FILE *fp;
    int num;
    struct user temp;

    num=0;

    if((fp=fopen(file,"rb"))==NULL)
    {
        printf("cannot open file!\n");
        exit(1);
    }

    while(fread(&temp,sizeof(struct user),1,fp))
    {
        num++;
    }

    fclose(fp);

    return num;
}
void getname(char *name)
{

    do
    {
        scanf("%s",name);
        fflush(stdin);

        if(strlen(name)==0)
            printf("姓名不能为空!\n");
        else if(strlen(name)>=20)
            printf("姓名不能超过20个字符!\n");
        else
            break;
        printf("重新输入姓名:  ");
    }
    while(1);

}
void getpassword(char *password)
{

    do
    {
        int i,j;
        char ch;

        for(i=0,j=0;; i++)
            if((ch=getchar())!='\n')
            {
                if(ch<='9'&&ch>='0')
                    password[i]=ch;
                else
                {
                    printf("密码只能是数字!\n");
                    j=1;
                    break;
                }
            }
            else
                break;
        password[i]='\0';

        if(j==1)
            continue;

        if(strlen(password)!=6)
            printf("密码只能是6位!\n");
        else
            break;
        printf("重新输入密码:  ");
    }
    while(1);
}


struct user getuser()
{
    void getname(char *name);
    void getpassword(char *password);

    struct user temp;

    printf("请输入用户姓名:  ");
    getname(temp.name);

    printf("请输入用户密码:  ");
    getpassword(temp.password);

    printf("输入开户金额:");
    do
    {
        scanf("%lf",&temp.money);
        fflush(stdin);

        if((temp.money)<10)
            printf("开户金额不能小于10\n");
        else
            break;

        printf("重新输入开户金额：");

    }
    while(1);

    return temp;
}

void select_name()
{
    void getname(char *name);
    void getpassword(char *password);
    printf("%30s\n","***按照姓名查询账户余额***");
    printf("%8s %15s %15s %10s\n","账号","用户姓名","存款余额");
    printf("---------------------------------------------\n\n\n");

    FILE * fp;
    struct user temp;
    char name[20];
    char password[8];

    if((fp=fopen(file,"rb"))==NULL)
    {
        printf("cannot open file!\n");
        exit(1);
    }

    printf("输入要查询的姓名:");
    getname(name);
    printf("请输入密码:");
    getpassword(password);

    while(fread(&temp,sizeof(struct user),1,fp))
        if(temp.id > 0 && strcmp(temp.name,name)==0)
        {
        	if(strcmp(temp.password,password)==0)
        	{
	        	printf("NO.%d %20s      %.2f\n",temp.id,temp.name,temp.money);
	        }else {
        		printf("您的帐号或密码不正确\n");
 		 	}
        }

    fclose(fp);

}
void select_id()
{
    int count();
    void getpassword(char *password);
    printf("%30s\n","***按照编号查询账户余额***");
    printf("%8s %15s %10s\n","编号","用户姓名","存款余额");
    printf("---------------------------------------------\n\n");

    FILE * fp;
    struct user temp;
    int i,maxnum;
    char password[8];

    if((fp=fopen(file,"rb"))==NULL)
    {
        printf("cannot open file!\n");
        exit(1);
    }

    maxnum=count();
    printf("输入要查询账号:");
    scanf("%d",&i);
    printf("输入账号密码:");
    scanf("%s",&password);
	if(i<1||i>maxnum)
    {
        printf("你要查询的账号不存在!");
        return;
    }

	int found = 0;
    while(fread(&temp,sizeof(struct user),1,fp))
        if(temp.id==i)
        {
        	found = 1;
        	if(strcmp(temp.password,password)==0) {
	        	printf("NO.%d %20s %.2f\n",temp.id,temp.name,temp.money);
	        }else {
        		printf("密码不正确\n");
        	}
        }
	if(found == 0) {
		printf("此账户不存在\n");
	}
    fclose(fp);

}
void display()
{
    printf("%30s\n","***用户资料显示***");
    printf("%8s %15s %10s\n","账号","用户姓名","存款余额");
    printf("---------------------------------------------\n\n");

    FILE * fp;
    struct user temp;

    if((fp=fopen(file,"rb"))==NULL)
    {
        printf("cannot open file!\n");
        exit(1);
    }

    while(fread(&temp,sizeof(struct user),1,fp))
    {
        printf("NO.%d %20s      %.2f\n",temp.id,temp.name,temp.money);
    }

    fclose(fp);

}
void save_money()
{
    printf("%30s\n","***用户存款业务***");
    printf("---------------------------------------------\n\n");

    int count();
    void getpassword(char *password);
    FILE *fp;
    int i,num,mark;
    struct user *temp;
    char password[8];
    num=count();
    temp=(struct user *)malloc(num*sizeof(struct user));

    if((fp=fopen(file,"rb"))==NULL)
    {
        printf("cannot open file!\n");
        exit(1);
    }

    for(i=0; i<num; i++)
        fread(&temp[i],sizeof(struct user),1,fp);

    fclose(fp);

    printf("输入要存款账号:");
    scanf("%d",&mark);
    if(mark<1||mark>num)
    {
        printf("你要存款账号不存在!");
        return;
    }
    printf("输入账号密码:");
    scanf("%s",&password);
    if((fp=fopen(file,"wb"))==NULL)
    {
        printf("cannot open file!\n");
        exit(1);
    }
    for(i=0; i<num; i++)
    {
        if(temp[i].id==mark)
        {
            double money=0;

            printf("输入要存入的金额:");
            scanf("%lf",&money);
            if(money<=0)
            {
                printf("只能为正数!\n");
                money=0;
            }
            temp[i].money +=money;
        }
        fwrite(&temp[i],sizeof(struct user),1,fp);

    }
    fclose(fp);
    free(temp);

    printf("你存款业务已办妥!\n");
}
void get_money()
{
    printf("%30s\n","***用户取款业务***");
    printf("---------------------------------------------\n\n");

    int count();
    void getpassword(char *password);
    FILE *fp;
    int i,num,mark;
    struct user *temp;
    char password[8];
    num=count();
    temp=(struct user *)malloc(num*sizeof(struct user));

    if((fp=fopen(file,"rb"))==NULL)
    {
        printf("cannot open file!\n");
        exit(1);
    }

    for(i=0; i<num; i++)
        fread(&temp[i],sizeof(struct user),1,fp);

    fclose(fp);

    printf("输入要取款账号:");
    scanf("%d",&mark);
    if(mark<1||mark>num)
    {
        printf("你要取款账号不存在!");
        return;
    }
    printf("输入账号密码:");
    scanf("%s",&password);

    if((fp=fopen(file,"wb"))==NULL)
    {
        printf("cannot open file!\n");
        exit(1);
    }
    for(i=0; i<num; i++)
    {
        if(temp[i].id==mark)
        {
            double money=0;

            printf("输入要取出的金额:");
            scanf("%lf",&money);
            if(money<=0)
            {
                printf("只能为正数!\n");
                money=0;
            }
            else if(money>temp[i].money)
            {
                printf("你的余额不足!\n");
                money=0;
            }
            temp[i].money -=money;
        }
        fwrite(&temp[i],sizeof(struct user),1,fp);

    }
    fclose(fp);
    free(temp);

    printf("你取款业务已办妥!\n");
}


void del()
{
    int count();
    printf("%30s\n","***注销账户***");
    printf("%8s %15s %10s\n","账号","用户姓名","存款余额");
    printf("---------------------------------------------\n\n");

    FILE * fp;
    struct user temp;
    struct user users[10]; 
    int index = 0;
    int i,maxnum;

    if((fp=fopen(file,"r"))==NULL)
    {
        printf("cannot open file!\n");
        exit(1);
    }
    maxnum=count();
    printf("输入要销户账号:");
    scanf("%d",&i);
    if(i<1||i>maxnum)
    {
        printf("你要查询的账号不存在!");
        return;
    }

	//是否找到 
	int found = 0;
    while(fread(&temp,sizeof(struct user),1,fp))//循环读取每一条记录  判断是否为要查看的记录
    {
        if(temp.id!=i)
        {
        	users[index ++] = temp;
        }else {
        	found = 1;
        }
    }

	fclose(fp);
	fp = fopen(file, "w");
	fclose(fp);
	
	fp = fopen(file, "ab");
    if(found == 1 && index > 0) {
    	for(int i = 0;i < index;i ++) {
	    	fwrite(&users[i], sizeof(struct user), 1, fp);
	    }
    }
    printf("注销成功\n");
    fclose(fp);
}


void print()	//函数功能：输出界面
{
    printf("%30s\n","***活期储蓄帐目管理系统***");
    printf("---------------------------------------------\n\n");
    printf("%8s,%-20s\n","1","用户开户");
    printf("%8s,%-20s\n","2","按照姓名查询账户余额");
    printf("%8s,%-20s\n","3","按照账号查询账户余额");
    printf("%8s,%-20s\n","4","存款");
    printf("%8s,%-20s\n","5","取款");
    printf("%8s,%-20s\n","6","用户销户");
    printf("%8s,%-20s\n","7","显示用户信息");
    printf("%8s,%-20s\n","8","退出");
    printf("\n请选择功能(1~8):");
}
void main()
{
    char choose;

    do
    {
        print();
        scanf(" %c",&choose);	//读取功能标号，根据标号选择不同的函数
        fflush(stdin);

        system("cls");
        switch(choose)
        {
        case '1':
            add();
            break;

        case '2':
            select_name();
            break;

        case '3':
            select_id();
            break;

        case '4':
            save_money();
            break;

        case '5':
            get_money();
            break;

        case '6':
            del();
            break;
        case '7':
            display();
            break;
        case '8':
            exit(1);
        default:
            printf("对不起，你所选择的功能不存在!\n");
        }
    }
    while(1);
}   

