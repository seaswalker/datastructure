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
    printf("%30s\n","***�û�����***");
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

    printf("�û������ɹ�!\n");

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
            printf("��������Ϊ��!\n");
        else if(strlen(name)>=20)
            printf("�������ܳ���20���ַ�!\n");
        else
            break;
        printf("������������:  ");
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
                    printf("����ֻ��������!\n");
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
            printf("����ֻ����6λ!\n");
        else
            break;
        printf("������������:  ");
    }
    while(1);
}


struct user getuser()
{
    void getname(char *name);
    void getpassword(char *password);

    struct user temp;

    printf("�������û�����:  ");
    getname(temp.name);

    printf("�������û�����:  ");
    getpassword(temp.password);

    printf("���뿪�����:");
    do
    {
        scanf("%lf",&temp.money);
        fflush(stdin);

        if((temp.money)<10)
            printf("��������С��10\n");
        else
            break;

        printf("�������뿪����");

    }
    while(1);

    return temp;
}

void select_name()
{
    void getname(char *name);
    void getpassword(char *password);
    printf("%30s\n","***����������ѯ�˻����***");
    printf("%8s %15s %15s %10s\n","�˺�","�û�����","������");
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

    printf("����Ҫ��ѯ������:");
    getname(name);
    printf("����������:");
    getpassword(password);

    while(fread(&temp,sizeof(struct user),1,fp))
        if(temp.id > 0 && strcmp(temp.name,name)==0)
        {
        	if(strcmp(temp.password,password)==0)
        	{
	        	printf("NO.%d %20s      %.2f\n",temp.id,temp.name,temp.money);
	        }else {
        		printf("�����ʺŻ����벻��ȷ\n");
 		 	}
        }

    fclose(fp);

}
void select_id()
{
    int count();
    void getpassword(char *password);
    printf("%30s\n","***���ձ�Ų�ѯ�˻����***");
    printf("%8s %15s %10s\n","���","�û�����","������");
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
    printf("����Ҫ��ѯ�˺�:");
    scanf("%d",&i);
    printf("�����˺�����:");
    scanf("%s",&password);
	if(i<1||i>maxnum)
    {
        printf("��Ҫ��ѯ���˺Ų�����!");
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
        		printf("���벻��ȷ\n");
        	}
        }
	if(found == 0) {
		printf("���˻�������\n");
	}
    fclose(fp);

}
void display()
{
    printf("%30s\n","***�û�������ʾ***");
    printf("%8s %15s %10s\n","�˺�","�û�����","������");
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
    printf("%30s\n","***�û����ҵ��***");
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

    printf("����Ҫ����˺�:");
    scanf("%d",&mark);
    if(mark<1||mark>num)
    {
        printf("��Ҫ����˺Ų�����!");
        return;
    }
    printf("�����˺�����:");
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

            printf("����Ҫ����Ľ��:");
            scanf("%lf",&money);
            if(money<=0)
            {
                printf("ֻ��Ϊ����!\n");
                money=0;
            }
            temp[i].money +=money;
        }
        fwrite(&temp[i],sizeof(struct user),1,fp);

    }
    fclose(fp);
    free(temp);

    printf("����ҵ���Ѱ���!\n");
}
void get_money()
{
    printf("%30s\n","***�û�ȡ��ҵ��***");
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

    printf("����Ҫȡ���˺�:");
    scanf("%d",&mark);
    if(mark<1||mark>num)
    {
        printf("��Ҫȡ���˺Ų�����!");
        return;
    }
    printf("�����˺�����:");
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

            printf("����Ҫȡ���Ľ��:");
            scanf("%lf",&money);
            if(money<=0)
            {
                printf("ֻ��Ϊ����!\n");
                money=0;
            }
            else if(money>temp[i].money)
            {
                printf("�������!\n");
                money=0;
            }
            temp[i].money -=money;
        }
        fwrite(&temp[i],sizeof(struct user),1,fp);

    }
    fclose(fp);
    free(temp);

    printf("��ȡ��ҵ���Ѱ���!\n");
}


void del()
{
    int count();
    printf("%30s\n","***ע���˻�***");
    printf("%8s %15s %10s\n","�˺�","�û�����","������");
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
    printf("����Ҫ�����˺�:");
    scanf("%d",&i);
    if(i<1||i>maxnum)
    {
        printf("��Ҫ��ѯ���˺Ų�����!");
        return;
    }

	//�Ƿ��ҵ� 
	int found = 0;
    while(fread(&temp,sizeof(struct user),1,fp))//ѭ����ȡÿһ����¼  �ж��Ƿ�ΪҪ�鿴�ļ�¼
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
    printf("ע���ɹ�\n");
    fclose(fp);
}


void print()	//�������ܣ��������
{
    printf("%30s\n","***���ڴ�����Ŀ����ϵͳ***");
    printf("---------------------------------------------\n\n");
    printf("%8s,%-20s\n","1","�û�����");
    printf("%8s,%-20s\n","2","����������ѯ�˻����");
    printf("%8s,%-20s\n","3","�����˺Ų�ѯ�˻����");
    printf("%8s,%-20s\n","4","���");
    printf("%8s,%-20s\n","5","ȡ��");
    printf("%8s,%-20s\n","6","�û�����");
    printf("%8s,%-20s\n","7","��ʾ�û���Ϣ");
    printf("%8s,%-20s\n","8","�˳�");
    printf("\n��ѡ����(1~8):");
}
void main()
{
    char choose;

    do
    {
        print();
        scanf(" %c",&choose);	//��ȡ���ܱ�ţ����ݱ��ѡ��ͬ�ĺ���
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
            printf("�Բ�������ѡ��Ĺ��ܲ�����!\n");
        }
    }
    while(1);
}   

