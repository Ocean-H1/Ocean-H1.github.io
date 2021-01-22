#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
struct student
{
	char name[10];
	char sex[5];
	char number[20];
	char major[10]; 
	struct student* next;
};

struct Node
{
	struct student data;
	struct Node* next;
};
struct Users
{
	char id[11];//用户名 
	char password[20];//密码 
	char tel[20];
};

struct Node* create_list(void);
struct Node* create_node(struct student);
void print_list(struct Node*); 
void insert_list(struct Node*,struct student);
void delete_list(struct Node*);
struct Node* search_list(struct Node*,char*);
void writeInfoToFile(struct Node* ,char* );
void readInfofromFile(struct Node*,char* );
void create_Users();
void registers();
int Login();
void reback();

void menu()
{
	printf("————————【学生信息管理系统】——————\n");
	printf("***1.【录入信息】***\n"); 
	printf("***2.【浏览信息】***\n");
	printf("***3.【删除信息】***\n");
	printf("***4.【查询信息】***\n");
	printf("***5.【修改信息】***\n");
	printf("***6.【数据排序】***\n");
	printf("***7.【退出系统】***\n");
	printf("————————————————————————\n");
		
}
void keydown(struct Node* pHead)
{
	
	struct student data;
	struct Node* pMove;
	int choice=0;
	printf("感谢使用，请选择要需要的菜单项-_-：\n");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:
			printf("——————√【录入信息】√——————\n");
			printf("请输入学生的姓名 性别 学号 专业班级\n");
			fflush(stdin);
			scanf("%s %s %s %s",data.name,data.sex,data.number,data.major);
			insert_list(pHead,data);
			break;
		case 2:
			printf("——————√【浏览信息】√——————\n");
			print_list(pHead);
			break;
		case 3:
			printf("——————√【删除信息】√——————\n");
			delete_list(pHead) ;
			break;
		case 4:
			printf("——————√【查询信息】√——————\n");
			printf("请输入要查找的学生姓名：\n");
			scanf("%s",data.name);
			pMove=search_list(pHead,data.name);
			if(pMove == NULL)
			{
				printf("未找到相关信息\n");
				system("pause");
			}
			else
			{
				printf("学生姓名——性别——学号——专业班级\n ");
				printf("%-5s  %-5s  %-8s  %-10s\n",pMove->data.name,pMove->data.sex,pMove->data.number,pMove->data.major);
			}
			
			break;
		case 5:
			printf("——————√【修改信息】√——————\n");
			printf("请输入要修改的学生姓名：\n");
			scanf("%s",data.name);
			pMove=search_list(pHead,data.name);
			if(pMove==NULL)
			{
				printf("未找到相关信息\n");
				system("pause");
			}
			else
			{
				printf("请输入修改后的学生信息：\n");
				
				if(scanf("%s%s%s%s",pMove->data.name,pMove->data.sex,pMove->data.number,pMove->data.major)==4)
				{
					printf("修改成功√√√\n");
				}
				else
				{
					printf("修改失败，请重试！\n");
				}
			}
			break;
		case 6:
			printf("——————【数据排序】√——————\n");
			printf("该功能正在开发中！\n");
			break;
		case 7:
			printf("您已成功退出系统，期待您的下次使用！！！\n");
			system("pause");
			exit(0);
			break;
		default:
			printf("选择错误，请重新输入\n");
			system("pause");
			break;
	}
		writeInfoToFile(pHead,"学生信息.txt");
}

int main(void)
{
	int status;
	struct Node* pHead=NULL;
	pHead=create_list();
	readInfofromFile(pHead,"学生信息.txt");
	create_Users();
	status=Login();
	while(status)
	{
		system("cls");
		Sleep(500);
		menu();
		keydown(pHead);
		system("pause");
		system("cls");
	 } 

	
	return 0;
}

struct Node* create_list(void)//创建链表
{
	struct Node* pHead=(struct Node*)malloc(sizeof(struct Node));
	pHead->next=NULL;
		
	return pHead;
}
struct Node* create_node(struct student data)
{
	struct Node* newNode =(struct Node*)malloc(sizeof(struct Node));
	newNode->data=data;
	newNode->next=NULL;
	
	
	return newNode;
}	
void print_list(struct Node* pHead)
{
	struct Node* pMove=pHead->next;
	printf("学生姓名——性别——学号——专业班级\n ");
	while(pMove!=NULL)
	{
		printf("%-5s  %-5s  %-8s  %-10s\n",pMove->data.name,pMove->data.sex,pMove->data.number,pMove->data.major);
		pMove=pMove->next;
	}
	printf("\n"); 
	
}
void insert_list(struct Node* pHead,struct student data)//新数据的插入 
{
	struct Node* pNew=create_node(data);
	pNew->next=pHead->next;
	pHead->next=pNew;
	
}
void delete_list(struct Node* pHead)
{
	char name[10];
	printf("请输入要删除的学生姓名\n");
	scanf("%s",name);
	struct Node* posNode=pHead->next;
	struct Node* posFrontnode=pHead;
	if(posNode==NULL)
	{
		printf("数据为空，无法删除\n");
		return ;
	}
	while(strcmp(posNode->data.name,name)!=0)
	{
		posFrontnode=posNode;
		posNode=posFrontnode->next;
		if(NULL==posNode)
		{
			printf("未找到指定位置无法删除\n");
			return ;
		}
	}
	
	posFrontnode->next=posNode->next;
	free(posNode);
	
}
struct Node* search_list(struct Node* pHead,char* name)
{
	struct Node* pMove=pHead->next;
	
	while(strcmp(pMove->data.name,name))
	{
		pMove=pMove->next;
		if(pMove==NULL)
		return NULL;
	}
	return pMove;
}
void readInfofromFile(struct Node* pHead,char* filename)
{
	FILE* fp;
	struct student data;
	fp = fopen(filename,"r");
	if(fp==NULL)
	{
		fp=fopen(filename,"w+");
	}
	while(fscanf(fp,"%s %s %s %s",data.name,data.sex,data.number,data.major)!=EOF)
	{
		insert_list(pHead,data);
	}
	
	fclose(fp);
}
void writeInfoToFile(struct Node* pHead,char* filename)
{
	FILE * fp;
	fp=fopen(filename,"w");
	if(fp==NULL)
	{
		printf("打开失败\n");
	}
	struct Node* pMove = pHead->next;
	while(pMove)
	{
		fprintf(fp,"%s %s %s %s\n",pMove->data.name,pMove->data.sex,pMove->data.number,pMove->data.major);
		pMove=pMove->next;
	}
	fclose(fp);
}
void create_Users()
{
	FILE * fp;
	
	if((fp=fopen("用户信息.txt","rb"))==NULL)
	{
		if((fp=fopen("用户信息.txt","wb+"))==NULL)
		{
			printf("无法建立该文件！\n");
			exit(0);
		}
	}
}
void registers()//注册新用户 
{
	struct Users a,b;
	FILE * fp;
	char temp[20];
	int count = 0;
	printf("欢迎来到注册界面！\n");
	Sleep(1000);
	fp = fopen("用户信息.txt","r");
	fread(&b,sizeof(struct Users),1,fp);
	printf("请输入您的用户名：\n");
	scanf("%s",a.id);
	while(1)
	{
		if(strcmp(a.id,b.id))
		{
			if(!feof(fp))
			{
				fread(&b,sizeof(struct Users),1,fp);
			}
			else
			{
				break;
			}
			
		}
		else
		{
			printf("此用户名已存在！请重新注册！\n");
			Sleep(1000);
			
		
		}
	}
	fclose(fp);
	printf("接下来输入您的电话号码用以日后找回密码：\n");
	scanf(" %s",a.tel);
	printf("接下来请输入您的密码（不超过20位）：\n");
	scanf(" %s",a.password);
	printf("请确认您的密码并再次输入：\n");
	scanf(" %s",temp);
	do{
		if(!strcmp(a.password,temp))
		{
			fp=fopen("用户信息.txt","a");
			fwrite(&a,sizeof(struct Users),1,fp);
			printf("账号注册成功，请登录！\n");
			Sleep(500);
			fclose(fp);
			return ;
		}
		else
		{
			printf("两次输入不一致请重新输入：\n");
			scanf(" %s",&a.password);
			printf("请确认密码并再输入一次：\n");
		}	scanf(" %s",&temp);
	}while(1);

}

int Login()//登录 
{
	int choice;
	struct Users a,b;
	FILE * fp;
	printf("欢迎使用学生信息管理系统，请先登录：\n");
	Sleep(1000);
	printf("***注册新用户输入 1\n");
	printf("***已有账号直接登陆输入 2\n");
	printf("***找回密码输入 3\n");
	
	scanf("%d",&choice); 
	while(1)
	{
		if(1==choice)
		{
			registers();
		}
		else if(3==choice)
		{
			reback();
		}
	
		else if(2==choice)
		{
			fp=fopen("用户信息.txt","r");
			fread(&b,sizeof(struct Users),1,fp);
			printf("请输入您的用户名以登录：\n");
			scanf(" %s",a.id);
			while(1)
			{
				if(strcmp(a.id,b.id)==0)
				{
					break;
				}
				else
				{
					if(!feof(fp))
					{	
						fread(&b,sizeof(struct Users),1,fp);
				
					}
					else
					{
						printf("此用户名不存在，请重新输入！\n");
						scanf(" %s",a.id);
						Sleep(500);
				
				
					}
				}
			}
				fclose(fp);
				printf("请输入您的密码：\n");
				scanf(" %s",a.password);
			do
			{
				if(strcmp(a.password,b.password)==0)
				{
					fclose(fp);
					printf("登录成功√欢迎您的使用！\n");
					Sleep(500);
					return 1;
				}
			else
			{
				printf("密码不正确！请重新输入密码：\n");
				scanf(" %s",a.password);
			}
			}while(strcmp(a.password,b.password) != 0);
	
			return 1;
		}
		else
		{
			printf("选择错误，请重新选择！\n");
			scanf("%d",&choice); 
		}
	
	 } 
	
}
void reback()//找回密码
{
	struct Users a,b;
	FILE * fp;
	char temp[20];
	int count = 0;
	printf("欢迎来到找回密码界面！\n");
	Sleep(1000);
	fp=fopen("用户信息.txt","r");
	fread (&b,sizeof(struct Users),1,fp);
	printf("请输入您的账号:\n");
	scanf(" %s",a.id);
	while(1)
	{
		if(strcmp(a.id,b.id)==0)
		{
			break;
		}
		else
		{
			if(!feof(fp))
			{
				fread(&b,sizeof(struct Users),1,fp);
				
			}
			else
			{
				printf("此用户名不存在，请重新输入！\n");
				scanf(" %s",a.id);
				Sleep(500);
			
			}
		}
	}
	fclose(fp);
	printf("请输入你的电话号码以验证身份：\n");
	scanf(" %s",a.tel);
	do{
		if(strcmp(a.tel, b.tel) !=0)
		{
			printf("电话号码不正确！请重新输入：\n");
			scanf(" %s",a.tel);
			
		}
	} while(strcmp(a.tel, b.tel) !=0);
	printf("身份验证通过！\n");
	printf("您的密码是：%s 请牢记！\n",b.password);
	Sleep(3000);

} 
