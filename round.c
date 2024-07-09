#include<stdio.h>

int procs, blocks=0, pointer;

struct process{
    int name, at, bt, ct, tat, wt, status, rem;
}proc[20], temp, queue[20], ready[20];

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
        printf("Process p%d(AT, BT): ", i);
        scanf("%d %d", &proc[i].at, &proc[i].bt);
        proc[i].status = 0;
        proc[i].rem = proc[i].bt;
    }
    sort();
}

void display(){
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0; i<procs; i++){
        printf("p%d\t%d\t%d\t%d\t%d\t%d\n", proc[i].name, proc[i].at, proc[i].bt, proc[i].ct, proc[i].tat, proc[i].wt);
    }

    printf("\nGANTT CHART\n");
    for(int i=0; i<blocks; i++){
        printf("----------");
    }
    printf("\n");
    for(int i=0; i<blocks; i++){
        if(queue[i].ct==0)
            printf("|  idle  |");
        else
           printf("|   p%d   |", queue[i].name);
    }
    printf("\n");
    for(int i=0; i<blocks; i++){
        printf("----------");
    }
    printf("\n");
    // printf("%d       ", queue[0].at);
    for(int i=0; i<blocks+1; i++){
        if(queue[i-1].ct==0)
            printf("%d         ", queue[i].at);
        else
            printf("%d         ", queue[i-1].ct);
    }
    // printf("HI%d", queue[0].at);
}

void enqueue(int x){
    ready[pointer] = proc[x];
    pointer++;

}

struct process dequeue(){
    struct process k = ready[0];
    for(int i=0; i<pointer-1; i++){
        ready[i] = ready[i+1];
    }
    pointer--;
    printf("\tct= pointer=%d", pointer);
    return k;

}

void robin(){
    int quantum, ct, done=0, min=-1;

    read();
    printf("\nEnter time quantum: ");
    scanf("%d", &quantum);

    if(proc[0].at > ct)
        blocks++;
    ct = proc[0].ct = proc[0].at + quantum;
    proc[0].rem -= quantum;
    proc[0].status = 1;
    queue[blocks] = proc[0];
    blocks++;
    if(proc[0].rem>0){
        for(int i=0; i<procs; i++){
            if(!proc[i].status && proc[i].at<=ct){
                enqueue(i);
                proc[i].status=1;
            }
        }
        enqueue(0);
    }

    while(done<procs){
        
        printf("\nready queue: ");
        for(int i=0; i<pointer; i++){
            printf("%d, ", ready[i].name);
        }

        for(int i=0; i<procs; i++){
            if(!proc[i].status && proc[i].at<=ct){
                enqueue(i);
                proc[i].status=1;
            }
        }


        if(pointer==0 && queue[blocks-1].rem==0){
            blocks++;
            for(int i=0; i<procs; i++){
                if(!proc[i].status){
                    min = i;
                }
            }
        }
        else if(pointer>0){
            temp = dequeue();
            for(int i=0; i<procs; i++){
                if(temp.name==i){
                    min=i;
                }
            }
        }
        else
            min=0;

        if(min==-1)
            return;
            // printf("ERROR\n");

        // proc[min].rem -= quantum;
        if(quantum >= proc[min].rem){
            // printf("###in here####");
            ct = proc[min].ct = ct + proc[min].rem;
            proc[min].tat = proc[min].ct - proc[min].at;
            proc[min].wt = proc[min].tat - proc[min].bt;
            proc[min].rem = 0;
            queue[blocks] = proc[min];
            blocks++;
            done++;
        }
        else{
            // printf("###out here####");
            ct = proc[min].ct = ct + quantum;
            proc[min].rem -= quantum;
            queue[blocks] = proc[min];
            blocks++;
            enqueue(min);
        }
    }
    display();
    printf("blocks=%d", blocks);
}

int main(){
    robin();
}