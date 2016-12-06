#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef int elemType;	//元素类型

typedef struct node{
	elemType data[MAXSIZE];
	int length;	//链表长度
} SeqList,* pSeqList;

//help Methods
//1.顺序表的初始化
pSeqList Init_SeqList(void);
//4.插入元素(将x插入顺序表第i个位置上，返回【1:成功；0:插入位置不合法；-1:溢出；-2:顺序表不存在】)
int Insert_SeqList(pSeqList pL,int i,elemType key);
//5.删除元素(删除第i个位置上的元素，返回【1:成功；0:删除位置不合法；-1:顺序表不存在】)
int Delete_SeqList(pSeqList pL,int i);


int Josephus_SeqList(pSeqList pL,int s,int m);


int main()
{
	pSeqList plA;
	plA= Init_SeqList();
	int i;
	for(i=1;i<11;i++)
	{
		Insert_SeqList(plA,i,2*i);
	}	
	Josephus_SeqList(plA,2,5);	
	return 0;
}

int Josephus_SeqList(pSeqList pL,int s,int m)
{
	int s1,i;
	if(pL==NULL)
	{
		printf("> 顺序表不存在\n");
		return -2;
	}
	if(pL->length==0)
	{
		printf("> 顺序表为空\n");
		return -1;
	}
	
	s1=s-1;
	for(i=pL->length;i>0;i--)
	{
		s1=(s1+m-1)%i;	//出列元素下标
		printf("\n出列：下标=%d;key=%d\n",s1,pL->data[s1]);		//
		Delete_SeqList(pL,s1+1);	//删除出列元素
	}
	return 1;
}



//构造一个空表，要返回该线性表，所以将返回一个指向顺序表的指针。
//首先动态分配存储空间，然后将表中的length置0，表示表中没有数据元素。
pSeqList Init_SeqList(void)
{
	printf("Init a Sequence List\n");
	pSeqList pL;
	pL=(pSeqList)malloc(sizeof(SeqList));
	if(pL!=NULL)	//pL=0表示分配失败
		pL->length=0;
	else
		printf("> malloc error\n");
	
	return pL;
}

//1.检查顺序表是否存在
//2.判断顺序表是否已满（超过MAXSIZE）
//3.判断插入位置的合法性(1<=i<=length+1)
//4.插入操作，修改表长
int Insert_SeqList(pSeqList pL,int i,elemType key)
{
	printf("顺序表插入：位置i=%d 插入key=%d\n",i,key);
	if(pL==NULL)
	{
		printf("> 顺序表不存在\n");
		return -2;
	}
	if(pL->length==MAXSIZE)
	{
		printf("> 顺序表已满\n");
		return -1;
	}
	if(i<1||i>pL->length+1)
	{
		printf("> 插入位置不合法\n");
		return 0;
	}
	int index=pL->length-1;	//从最后一个元素开始，每个元素往后移动一个位置。
	while(index>=i-1)
	{
		pL->data[index+1]=pL->data[index];
		index--;
	}
	pL->data[i-1]=key;	//i位置上插入key
	pL->length++;	//将顺序表长度加1
	
	return 1;
}

//1.检查顺序表是否存在
//2.判断删除位置的合法性(1<=i<=length+1)
//3.删除操作，修改表长
int Delete_SeqList(pSeqList pL,int i)
{
	printf("顺序表删除：位置i=%d \n",i);
	if(pL==NULL)
	{
		printf("> 顺序表不存在\n");
		return -1;
	}
	if(i<1||i>pL->length)
	{
		printf("> 删除位置不合法i=%d ;length=%d \n",i,pL->length);
		return 0;
	}
	
	int index=i;	//从第i个元素开始，每个元素往前移动一个位置
	while(index<pL->length)
	{
		pL->data[index-1]=pL->data[index];
		index++;
	}
	pL->length--;
	
	return 1;
}

