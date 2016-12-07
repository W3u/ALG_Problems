#include <stdio.h>
#include <stdlib.h>

typedef int dataType;	//元素类型

typedef struct sNode{
	dataType data;	//存放数据信息
	struct sNode* next;	//存放后继元素的地址 
} LNode,*pLinkList;

//1.创建（不带头结点）循环链表
pLinkList Create_LinkList(dataType key);
//2.链表的长度
int Length_LinkList(pLinkList pFirst);
//3.按序号查找 
pLinkList Location_LinkList_Pos(pLinkList pFirst,int i);
//4.插入元素(将x插入链表第i个位置上，返回【1:成功；0:malloc error；-1:位置不合法；-2:链表不存在】)
int Insert_LinkList(pLinkList pFirst,int i,dataType key);
//5.遍历链表
void Print_LinkList(pLinkList pFirst);

int Josephus_LinkedList(pLinkList pFirst,int s,int m);



int main()
{
	pLinkList pFirst=Create_LinkList(1);
	int i;
	for(i=2;i<11;i++)
	{
		Insert_LinkList(pFirst,i,2*i);
	}
	
	printf("初始化：\n");
	Print_LinkList(pFirst);
	Josephus_LinkedList(pFirst,2,5);
	Print_LinkList(pFirst);
	
	return 0;
}

//1.创建（不带头结点）循环链表
pLinkList Create_LinkList(dataType key)
{
	pLinkList pFirst=(pLinkList)malloc(sizeof(LNode));
	if(pFirst==NULL)
	{
		printf("malloc error\n");
		return NULL;
	}
	pFirst->data=key;
	pFirst->next=pFirst;
	return pFirst;
}

//2.链表的长度
int Length_LinkList(pLinkList pFirst)
{
	if(pFirst==NULL)
	{
		printf("单链表不存储\n");
		return 0;
	}
	if(pFirst->next==pFirst)
	{
		return 1;
	}
	int length=1;
	pLinkList pNode=pFirst->next;
	while(pNode!=pFirst)
	{
		length++;
		pNode=pNode->next;
	}
	return length;
}

//3.按序号查找 
pLinkList Location_LinkList_Pos(pLinkList pFirst,int i)
{
	int length=Length_LinkList(pFirst);
	if(pFirst==NULL)
	{
		printf("链表不存在\n");
		return NULL;
	}
	if(i<1||i>length)
	{
		printf("查找位置i超出范围\n");
		return NULL;
	}
	int count=1;
	pLinkList pNode=pFirst;
	while(1)
	{
		if(count==i)
			return pNode;
		else
		{
			pNode=pNode->next;
			count++;
		}
	}
}

//4.插入元素(将x插入链表第i个位置上，返回【1:成功；0:插入位置不合法；-1:溢出；-2:链表不存在】)
int Insert_LinkList(pLinkList pFirst,int i,dataType key)
{
	int length=Length_LinkList(pFirst);
	if(pFirst==NULL)
	{
		printf("链表不存在\n");
		return -2;
	}
	if(i<1||i>length+1)
	{
		printf("插入位置不合法\n");
		return -1;
	}
	pLinkList newNode=(pLinkList)malloc(sizeof(LNode));
	if(newNode==NULL)
	{
		printf("malloc error");
		return 0;
	}
	//获得第i-1个位置的结点
	pLinkList preNode=Location_LinkList_Pos(pFirst,i-1);	
	
	newNode->data=key;
	newNode->next=preNode->next;
	preNode->next=newNode;	//newNode在第i个位置
	return 0;
}

//5.遍历链表
void Print_LinkList(pLinkList pFirst)
{
	if(pFirst==NULL)
	{
		printf("单链表不存在");
		return;
	}
	if(pFirst->next==pFirst)
	{
		printf("%d \n",pFirst->data);
		return;
	}
	pLinkList pNode=pFirst->next;
	while(pNode!=pFirst)
	{
		printf("%d ",pNode->data);
		pNode=pNode->next;
	}
	printf("\n");
}


int Josephus_LinkedList(pLinkList pFirst,int s,int m)
{
	if(m<1)
	{
		printf("m无效\n");
		return -1;
	}
	printf("输出约瑟夫序列：\n");
	int count=1;	//计数
	pLinkList preNode=Location_LinkList_Pos(pFirst,s-1);
	pLinkList pNode=preNode->next;
	while(pNode!=NULL&&pNode->next!=pNode)
	{
		if(count==m)
		{//出列
			printf("%d ",pNode->data);
			preNode->next=pNode->next;
			free(pNode);
			pNode=preNode->next;
		}
		else
		{
			count++;
		}
		preNode=pNode;
		pNode=pNode->next;
	}
	printf("%d\n",pNode->data);
	free(pNode);
	return 1;
}





