#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdlib.h>

struct node{
    int pno;
    int bt;
    //int at;
    int pri;
    struct node*next;
};

int cnodes=0;

struct node* insertrear( struct node * head,int pno,int bt,int pri){
    struct node*n1,*temp;
    n1=(struct node*)malloc(sizeof(struct node));
    if (n1==NULL){
        printf("sorry memory full");
        return n1;
    }
    cnodes++;
    n1->pno=pno;
    n1->pri=pri;
    n1->bt=bt;
    n1->next=NULL;
    if(head==NULL){

        head=n1;
        return head;
    }
    
    temp=head;
    while(temp->next!=NULL){
         temp=temp->next;
        }
    temp->next=n1;
   
    //printf("%p",&head);
    return head;
}

void fifo(struct node*head){
    int wt[100];
    int tt[100];
    int i=0;
    struct node*temp;
    temp=head;
    while(temp!=NULL){
        if (i==0){
            wt[i]=0;
            tt[i]=temp->bt-0;
            i++;
        }
        else{
            wt[i]=tt[i-1];
            tt[i]=temp->bt+wt[i];
            i++;
        }
        temp=temp->next;
    }
    float wait=0;
    float turn=0;
    for (i=0;i<cnodes;i++){
        wait=wait+wt[i];
        turn=turn+tt[i];
    }
    float w,t;
    w=wait/cnodes*1.0;
    t=turn/cnodes*1.0;
    printf("average waiting time of process is %.2f\t",w);
    printf("average turnaround time of proccess is %.2f\n",t);
}

void swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 

void sjf(struct node*head){
    struct node*temp;
    struct node*head2=NULL;
    int btarr[25],pno[25],prio[25];
    int i=0, j;
    temp=head;
    while(temp!=NULL){
        //printf("hi");
        btarr[i]=temp->bt;
        pno[i]=temp->pno;
        prio[i]=temp->pri;
      
        temp=temp->next;
        i++;
    }
   
    int k=cnodes;
   for (i = 0; i < cnodes-1; i++){       
       for (j = 0; j < cnodes-i-1; j++) {
           if (btarr[j] >btarr[j+1]){
              swap(&btarr[j], &btarr[j+1]);
              swap(&pno[j], &pno[j+1]);
              swap(&prio[j], &prio[j+1]);}
              
       }
   }
  
    for (i=0;i<k;i++){
        head2=insertrear(head2,pno[i],btarr[i],prio[i]);
   }
   cnodes=k;
    fifo(head2);
}
void priority( struct node*head){
    struct node*temp;
    struct node*head3=NULL;
    int btarr[100],pno[100],prio[100];
    int i=0, j;
    temp=head;
    while(temp!=NULL){
        btarr[i]=temp->bt;
        pno[i]=temp->pno;
        prio[i]=temp->pri;
        temp=temp->next;
        i++;
    }
    int k=cnodes;
   for (i = 0; i < k-1; i++){       
       for (j = 0; j < k-i-1; j++) {
           if (prio[j] >prio[j+1])
              swap(&btarr[j], &btarr[j+1]);
              swap(&pno[j], &pno[j+1]);
              swap(&prio[j], &prio[j+1]);
           
       }
   }
   for (i=0;i<k;i++){
       head3=insertrear(head3,pno[i],btarr[i],prio[i]);
   }
   cnodes=k;
   fifo(head3);
}


void display(struct node*head){
    struct node*temp;
    int i;
    temp=head;
    printf("PROCESS NUMBER|BURST TIME|PRIORITY\n");
    for(i=0;i<cnodes;i++){
        printf("%d|%d|%d  \n",temp->pno,temp->bt,temp->pri);
        //printf("%p",&temp->next);
        temp=temp->next;
    }
    //printf("hello");
    return;
}

void main(){
    int pri;
    int bt;
    int pno;
    int ch;
    struct node* head=NULL;
    printf("INSERT NODES");
    printf("enter process no:");
    scanf("%d",&pno);
    printf("enter burst time:");
    scanf("%d",&bt);
    printf("enter the priority of the process:");
    scanf("%d",&pri);
    head=insertrear(head,pno,bt,pri);
    for(;;){
        printf("would you like to keep inserting\n ");
        printf("enter 1 for yes press any other key for no");
        scanf("%d",&ch);
        switch(ch){
            case 1:printf("INSERT NODE\n");
                   printf("enter process no:");
                   scanf("%d",&pno);
                   printf("enter burst time:");
                   scanf("%d",&bt);
                   printf("enter the priority of the process:");
                   scanf("%d",&pri);
                   head=insertrear(head,pno,bt,pri);
                   break;
            default:display(head);
                     printf("FIFO\n");
                    fifo(head);
                   printf("SJF\n");
                   sjf(head);
                   printf("PRIORITY\n");
                   priority(head);
                   exit(0);
        }
    }
}

///home/samarth/Documents/diary manager/proccess_scheduling.c