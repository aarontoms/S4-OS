#include <stdio.h>
#include<stdbool.h>

int procs=0, ch, blocks=0, ready_pointer=0;
bool idle=true;

struct process{
    int name, at, bt, ct, tat, wt, prior, status, rem;
}proc[20], temp, queue[20], ready[20];

void sortready(){
    for(int i=0; i<ready_pointer-1; i++){
        for(int j=0; j<ready_pointer-i-1; j++){
            if(ch==2){
                if(ready[j].bt > ready[j+1].bt){
                    temp = ready[j];
                    ready[j] = ready[j+1];
                    ready[j+1] = temp;
                }
            }
            else if(ch==3){
                if(ready[j].prior > ready[j+1].prior){
                    temp = ready[j];
                    ready[j] = ready[j+1];
                    ready[j+1] = temp;
                }
            }
        }
    }
    // printf("\nready queue: ");
    // for(int i=0; i<ready_pointer; i++){
    //     printf("%d ", ready[i].prior);
    // }
    // printf("\n");

    if(ready_pointer==0)
        idle = true;
    else
        idle = false;
}

void enqueue(int x){
    // printf("\nprocs=%d", procs);
    ready[ready_pointer] = proc[x];
    ready_pointer++;
}

int dequeue(){
    sortready();
    int k;

    if(ready_pointer==0){
        for(int i=0; i<procs; i++){
            if(!proc[i].status){
                k=i;
                break;
            }
        }
    }
    else{
        k = ready[0].name;
        for(int i=0; i<ready_pointer; i++){
            ready[i] = ready[i+1];
        }
        ready_pointer--;
        for(int i=0; i<procs; i++){
            if(proc[i].name==k){
                k=i;
                break;
            }
        }
    }

    // printf("returned priority: %d ", proc[k].name);
    return k;
}

void sort(){
    for(int i=0; i<procs-1; i++){
        for(int j=0; j<procs-i-1; j++){
            if(proc[j].at > proc[j+1].at){
                temp = proc[j];
                proc[j] = proc[j+1];
                proc[j+1] = temp;
            }
        }
    }
}

void read(){
    printf("Enter the number of processes: ");
    scanf("%d", &procs);
    printf("---ENTER DETAILS---\n");
    for(int i=0; i<procs; i++){
        proc[i].name = i;
        if(ch==3){
            printf("Process p%d(AT, BT, Priority): ", i);
            scanf("%d %d %d", &proc[i].at, &proc[i].bt, &proc[i].prior);
        }
        else{
            printf("Process p%d(AT, BT): ", i);
            scanf("%d %d", &proc[i].at, &proc[i].bt);
        }
        proc[i].status = 0;
        proc[i].rem = proc[i].bt;
    }
    sort();
}

void display(){
    printf("printed %d lines\n", procs);
    printf("\n\nProcess\tAT\tBT\tCT\tTAT\tWT\tPriority\n");
    for(int i=0; i<procs; i++){
        printf("p%d\t%d\t%d\t%d\t%d\t%d\t%d\n", proc[i].name, proc[i].at, proc[i].bt, proc[i].ct, proc[i].tat, proc[i].wt, proc[i].prior);
    }

    //Gantt
    printf("Gantt Chart\n");
    printf("added to queue at pos %d and ct=%d", blocks, queue[0].ct);

    for(int i=0; i<blocks; i++){
        printf("--------");
    }
    printf("\n");
    for(int i=0; i<blocks; i++){
        if(queue[i].ct == 0)
            printf("| ati%d |", i);
        else
            printf("|  p%d  |", queue[i].name);
    }
    printf("\n");
    for(int i=0; i<blocks; i++){
        printf("--------");
    }
    printf("\n");
    // printf("%d       ", proc[0].at);
    for(int i=0; i<blocks+1; i++){
        if(queue[i-1].ct == 0)
            printf("%d       ", queue[i].at);
        else
            printf("%d       ", queue[i-1].ct);
    }
    // printf("%d", queue[blocks-1].ct);
}

void fcfs(){
    read();

    for(int i=0; i<procs; i++){
        if(proc[i].at > proc[i-1].ct)
            blocks++;
        if(proc[i].at > proc[i-1].ct)
            proc[i].ct = proc[i].at + proc[i].bt;
        else
            proc[i].ct = proc[i-1].ct + proc[i].bt;

        proc[i].tat = proc[i].ct - proc[i].at;
        proc[i].wt = proc[i].tat - proc[i].bt;
        queue[blocks] = proc[i];
        blocks++;
    }
    display();
}

void sjf(){
    read();
    int done=0, ct, min, flag, prev;

    if(proc[0].at > 0)
        blocks++;
    
    ct = proc[0].ct = proc[0].at + proc[0].bt;
    proc[0].tat = proc[0].ct - proc[0].at;
    proc[0].wt = proc[0].tat - proc[0].bt;
    proc[0].status = 1;
    done++;
    queue[blocks] = proc[0];
    prev = 0;
    blocks++;

    while(done < procs){

        for(int i=0; i<procs; i++){
            if(!proc[i].status){
                min = i;
                break;
            }
        }
        flag=0;
        for(int i=0; i<procs; i++){
            if(proc[i].at<=ct && proc[i].status==0){
                flag = 1;
                // printf("keri ");
                // printf("BURSTS: %d vs %d\n", proc[i].bt, proc[min].bt);
                if(proc[i].bt < proc[min].bt)
                    min = i;
            }
        }

        if(flag==0)
            blocks++;

        if(proc[min].at > ct)
            proc[min].ct = proc[min].at + proc[min].bt;
        else
            proc[min].ct = proc[prev].ct + proc[min].bt;
        proc[min].tat = proc[min].ct - proc[min].at;
        proc[min].wt = proc[min].tat - proc[min].bt;
        proc[min].status=1;
        done++;
        queue[blocks]=proc[min];
        blocks++;
        prev = min;
        printf("MIN=%d ", min);
    }
    display();
    //try alternate method by adding all arrived but unfinished ones to ready queue and then sorting based on the burst time to find min
}
//sortready in priority and then if idle then no need to run dequeue at all
void priority(){
    read();
    int prev, ct=0, done=0, min;

    if(proc[0].at > 0)
        blocks++;
    
    ct = proc[0].ct = proc[0].at + proc[0].bt;
    proc[0].tat = proc[0].ct - proc[0].at;
    proc[0].wt = proc[0].tat - proc[0].bt;
    proc[0].status=1;
    done++;
    queue[blocks] = proc[0];
    blocks++;

    while(done<procs){
        for(int i=0; i<procs; i++){
            if(!proc[i].status && proc[i].at<=ct){
                proc[i].status=1;
                enqueue(i);
            }
        }
        sortready();
        min = dequeue();


        if(!idle)
            ct=proc[min].ct = queue[blocks-1].ct + proc[min].bt;
        else if(idle){
            blocks++;
            ct=proc[min].ct = proc[min].at + proc[min].bt;
        }
        proc[min].tat = proc[min].ct - proc[min].at;
        proc[min].wt = proc[min].tat - proc[min].bt;
        done++;
        queue[blocks] = proc[min];
        blocks++;
        // printf("\nMIN=%d ", min);
    }
    display();
}

int main(){
    printf("Scheduling:\n 1. FCFS\n 2. SJF\n 3. Priority\n 4. Round Robin\nEnter your choice: ");
    scanf("%d", &ch);
    switch(ch){
    case 1:
        fcfs();
        break;
    case 2:
        sjf();
        break;
    case 3:
        priority();
        break;
    case 4:
        // robin();
        break;
    }
}
