#include <stdio.h>
#include <stdlib.h>
#define NUM 5           //�w�q��C�j�p

void addQueue(int);      //�ŧiaddQueue�Ƶ{��
int deletQueue(void);      //�ŧideletQueue�Ƶ{��
void printQueue(void);  //�ŧi�C�L�ثe���Φ�C�����e���Ƶ{��

typedef struct queue {
  int CQueue[NUM];
  int Rear;
  int Front;
} Queue;
Queue qu;

int main(void) {  //�D�{��

    int op=0,item;
    qu.Rear = 0;
    qu.Front = 0;
        printf("===============�{���y�z===========================\n");
        printf("= �{���ت��G���Φ�C�i��Add Queue�H��Delet Queue =\n"); 
        printf("==================================================\n");   
    while(1) {
        printf("==============================================\n");
        printf("=   1.Add Queue(�[�J)                        =\n");
        printf("=   2.Delete Queue(�R��)                     =\n");
        printf("=   3.��ܥثe���Φ�C�����e                 =\n");
        printf("=   4.����                                   =\n");    
        printf("==============================================\n");
        printf("�п�J�A���ާ@�G");
        scanf("%d",&op);
        switch(op) {
            case 1: printf("�п�J�A�n�[�J�����:");
                scanf("%d",&item);
                addQueue(item);
                break;
            case 2: item = deletQueue( );
                if(item != -1)
                    printf("%d �O�q���Φ�C�R�������\n",item);
                break;
            case 3: printQueue( );
                break;
            case 4: printf("\n");       //����
                return (0);  
       }
    }
  system("pause");     //�ϵ{���Ȱ��b����e�����ڭ̬ݨ쵲�G
  return 0;
}

void addQueue(int item) {  //�[�Jitem���C�����Ƶ{��

  qu.Rear = (qu.Rear+1)%NUM;
  if((qu.Rear)%NUM == qu.Front) {
    printf("���Φ�C�O����!\n");
    system("pause");
    exit(1);
  } else
    qu.CQueue[qu.Rear] = item;
}

int deletQueue(void) { //�q��C���R��item

  if(qu.Front == qu.Rear) {
    printf("���Φ�C�O�Ū�!\n");
    system("pause");
    exit(1);
  } else {
    qu.Front = (qu.Front+1)%NUM;
    return qu.CQueue[qu.Front];
  }  
}

void printQueue(void)   //��ܥثe���Φ�C�����e���Ƶ{��
{
  int i;
  printf("�ثe���Φ�C�����e�G");
  for(i=qu.Rear;i!=qu.Front;i=(i+NUM-1)%NUM)
    printf("%d ",qu.CQueue[i]);
  printf("\n");  
}
