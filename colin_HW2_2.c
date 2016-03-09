/*
 ============================================================================
 Name        : HW2.c
 Author      : Colin
 Version     :1.0
 Copyright   : Your copyright notice
 Description : Pthread/system time/linked list in C
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include<string.h>
//#define NUM_THREADS     5

int year, month, day, hour, min, sec;

/* 定義結構型態 */
typedef struct link_node{
   int data;
   char timeBuffer[50];
   struct link_node *link;
} LINK_NODE;

LINK_NODE *list=NULL;

/* 產生新節點 */
LINK_NODE *new_node(int data, char* timeBuffer){
   LINK_NODE *node;
   node=(LINK_NODE *) malloc(sizeof(LINK_NODE));/*<stdlib.h>*/

   // 記憶體不足
   if(node == NULL){ return NULL;}

   node->data=data;
   sprintf(node->timeBuffer,"%s",timeBuffer);
   node->link=NULL;
   return node;
}


/* 加入新的資料於最後 */
LINK_NODE *push_node(LINK_NODE *list, int data, char* timeBuffer){
   /*產生新節點*/
   LINK_NODE *node=new_node(data, timeBuffer);

   // 加入第一個新節點
   if(list==NULL){
       list=node;
   }else{
       LINK_NODE *p=list;
       // 取得最後一個節點
       while(p->link!=NULL){p=p->link;}
       p->link=node;
   }
   return list;
}


/* 排序插入新節點 */
LINK_NODE *sort_insert(LINK_NODE *list,int data, char* timeBuffer){
   // 加入第一筆資料

   // 產生新節點
   LINK_NODE *node=new_node(data, timeBuffer);
   if(list==NULL){ list=node; return list; }

   // 尋找大於資料(data)的位址
   LINK_NODE *r=list,*q=list;
   while(r!=NULL && r->data<data){ q=r; r=r->link; }

   if(r==list){ // 首節點
       node->link=list; list=node;
   }else{ // 加入新節點於中間
       node->link=q->link;
       q->link=node;
   }
   return list;
}


/* 計算串列長度 */
int get_length(LINK_NODE *list){
   LINK_NODE *p=list;
   int count=0;
   while(p!=NULL){
       count++;
       p=p->link;
   }

   return count;
}


/* 搜尋資料(data)的節點位子 */
LINK_NODE *search_node(LINK_NODE *list, int data){
   LINK_NODE *p=list;
   while(p!=NULL && p->data!=data){ p=p->link; }
   return p ;
}


/* 印出所有串列的所有資料 */
int display(LINK_NODE *list){
   LINK_NODE *p=list;
   while(p!=NULL){
       printf("%s\n",p->timeBuffer);/*<stdio.h>*/
       p=p->link;
   }
   return 1;
}


void *getSystemTime(){

	char timeBuffer[50];
	int NUM;
	while(1){
		time_t t = time(NULL);
			struct tm tm = *localtime(&t);
			year = tm.tm_year + 1900;
			month = tm.tm_mon + 1;
			day = tm.tm_mday;
			hour = tm.tm_hour;
			min = tm.tm_min;
			sec = tm.tm_sec;

			//printf("getSystemTime: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
			printf("getSystemTime: %d-%d-%d %d:%d:%d\n", year, month, day, hour, min, sec);
			sprintf(timeBuffer," %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
			list=push_node(list, NUM, timeBuffer);

			sleep(1);
			NUM++;
	}
	//return timeBuffer;
}

void *printGetSystemTime(void){

    while(1){
    	printf("printgetSystemTime: %d-%d-%d %d:%d:%d\n", year, month, day, hour, min, sec);
    	display(list);
    	sleep(1);
    }
    return NULL;
}

int main (){
    pthread_t getSystemTimeThreadId, printGetSystemTimeThreadId;

    pthread_create(&getSystemTimeThreadId,NULL,&getSystemTime,NULL);
/*
    {
    	LINK_NODE *list=NULL;
    	char timeBuffer[50];
    	getSystemTime(timeBuffer);
    	list=push_node(list,timeBuffer);
    }
*/
    pthread_create(&printGetSystemTimeThreadId,NULL,&printGetSystemTime,NULL);

    while(1){
        sleep(1);
    }

    return 0;
    //pthread_exit(NULL);
}
