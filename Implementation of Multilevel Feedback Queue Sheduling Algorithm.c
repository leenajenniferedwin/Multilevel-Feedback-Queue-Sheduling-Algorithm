#include<stdio.h>
#include<stdlib.h>

struct process
{
    char name;
int AT,BT,WT,TAT,RT,CT,P;
}Q1[10],Q2[10],Q3[10];/*Three queues*/

int n=0;
void sortByArrival_priority()
{
struct process temp;
int i,j;
for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
            {
                if(Q1[i].AT>Q1[j].AT)
                    {
                          temp=Q1[i];
                          Q1[i]=Q1[j];
                          Q1[j]=temp;
                    }
            }
    }

for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
            {
                if(Q1[i].AT==Q1[j].AT)
                    {
			    if(Q1[i].P > Q1[j].P)
			    {
				temp=Q1[i];
                         	Q1[i]=Q1[j];
                          	Q1[j]=temp;
			}
                    }
            }
    }

}
int main()
{
int i,j,k=0,r=0,time=0,tq1=8,tq2=16,flag=0,temp,z;
     char c;
printf("Enter no of processes:");
scanf("%d",&n);
int p[n],su[n];
     for(i=0,c='A';i<n;i++,c++)
     {
         Q1[i].name=c;
printf("\nEnter the arrival time and burst time of process %c: ",Q1[i].name);
scanf("%d%d",&Q1[i].AT,&Q1[i].BT);
         Q1[i].RT=Q1[i].BT;/*save burst time in remaining time for each process*/
printf("Is process %c System/User Process (0/1) ? --- ",c);
scanf("%d", &Q1[i].P);

    }

sortByArrival_priority();

time=Q1[0].AT;
printf("Process in first queue following RR with qt=8");
printf("\nProcess\t\tBT\t\tWT\t\tTAT\t\tCT");
for(i=0;i<n;i++)
{

  if(Q1[i].RT<=tq1)
  {

	if(time < Q1[i].AT){

		time = Q1[i].AT;
	}

       time+=Q1[i].BT;/*from arrival time of first process to completion of this process*/
       Q1[i].WT=time-Q1[i].AT-Q1[i].BT;/*amount of time process has been waiting in the first queue*/
       Q1[i].TAT=time-Q1[i].AT;/*amount of time to execute the process*/
       printf("\n%c\t\t%d\t\t%d\t\t%d\t\t%d\n",Q1[i].name,Q1[i].BT,Q1[i].WT,Q1[i].TAT,time);

  }
  else/*process moves to queue 2 with qt=16*/
  {
      if(time < Q1[i].AT){
	
	      time=Q1[i].AT;
      }

      time+=tq1;
      Q1[i].RT-=tq1;
      Q2[k].RT=Q1[i].RT;
      Q2[k].BT=Q1[i].BT;
      Q2[k].name=Q1[i].name;
      Q2[k].AT = Q1[i].AT;
      k=k+1;
      flag=1;
   }
}

if(flag==1)
{
printf("\nProcess in second queue following RR with qt=16");
printf("\nProcess\t\tBT\t\tWT\t\tTAT\t\tCT");
for(i=0;i<k;i++)
   {
    
	if(Q2[i].RT<=tq2)
     {

       time+=Q2[i].RT;/*from arrival time of first process +BT of this process*/
       Q2[i].WT=time-Q2[i].AT-tq1-Q2[i].RT;/*amount of time process has been waiting in the ready queue*/
       Q2[i].TAT=time-Q2[i].AT;/*amount of time to execute the process*/
       printf("\n%c\t\t%d\t\t%d\t\t%d\t\t%d\n",Q2[i].name,Q2[i].BT,Q2[i].WT,Q2[i].TAT,time);

    }

    else/*process moves to queue 3 with FCFS*/
    {
      Q3[r].AT=Q2[i].AT;
      time+=tq2;
      Q2[i].RT-=tq2;
      Q3[r].RT=Q2[i].RT;
      Q3[r].BT=Q2[i].BT;
      Q3[r].name=Q2[i].name;
      r=r+1;
      flag=2;
    }
  }
}

if(flag==2){
printf("\nProcess in third queue following FCFS ");
printf("\nProcess\t\tBT\t\tWT\t\tTAT\t\tCT");
for(i=0;i<r;i++)
{
    if(i==0)
            Q3[i].CT=Q3[i].RT+time;
        else
            Q3[i].CT=Q3[i-1].CT+Q3[i].RT;

}

for(i=0;i<r;i++)
    {
        Q3[i].TAT=Q3[i].CT - Q3[i].AT;
        Q3[i].WT=Q3[i].TAT - Q3[i].BT;
	printf("\n%c\t\t%d\t\t%d\t\t%d\t\t%d\n",Q3[i].name,Q3[i].BT,Q3[i].WT,Q3[i].TAT,Q3[i].CT);

    }

}
}
