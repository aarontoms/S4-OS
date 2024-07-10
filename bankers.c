#include<stdio.h>

int max[10], avail[10];

struct process{
    int name, done;
    int alloc[10], max[10], need[10];
}p[10];

void main(){
    int resource, procs, done=0, flag, i, j, var=0, rear=0;
    int queue[10];

    printf("Enter the number of resource types: ");
    scanf("%d", &resource);
    printf("Enter the maximum instances of each resource: ");
    for(int i=0; i<resource; i++){
        scanf("%d", &max[i]);
        avail[i] = max[i];
    }
    printf("\nEnter number of processes: ");
    scanf("%d", &procs);

    for(int i=0; i<procs; i++){
        p[i].name = i;
        p[i].done = 0;

        printf("\np%d - ALLOC: ", p[i].name);
        for(int j=0; j<resource; j++){
            scanf("%d", &p[i].alloc[j]);
        }
        printf("MAXREQ: ");
        for(int j=0; j<resource; j++){
            scanf("%d", &p[i].max[j]);
            p[i].need[j] = p[i].max[j] - p[i].alloc[j];
            avail[j] -= p[i].alloc[j];
        }
    }

    printf("\nProcess\t  Alloc\t\tMax\t\tNeed\n");
    for(int i=0; i<procs; i++){
        printf("p%d\t", p[i].name);
        for(int j=0; j<resource; j++){
            printf("%d ", p[i].alloc[j]);
        }
        printf("\t");
        for(int j=0; j<resource; j++){
            printf("%d ", p[i].max[j]);
        }
        printf("\t");
        for(int j=0; j<resource; j++){
            printf("%d ", p[i].need[j]);
        }
        printf("\n");
    }

    for(i=0; i<procs;){
        for(j=0, flag=0; j<resource; j++){
            if(avail[j]>=p[i].need[j]){
                flag++;
            }
            if(p[i].need[j]>max[j])
                var=0;
        }
        if(flag==resource && !p[i].done){
            p[i].done = 1;
            for(int m=0; m<resource; m++){
                avail[m] += p[i].alloc[m];
            }
            done++;
            var=1;
            queue[rear] = i;
            rear++;
        }
        else{
            i++;
            if(i==procs){
                if(var==0){
                    printf("Deadlock\n");
                    return;
                }
                i=0;
            }
        }

        int k;
        for(k=0; k<procs; k++){
            if(!p[k].done){
                break;
            }
        }
        if(k==procs){
            printf("Safe Sequence: < ");
            for(int m; m<rear; m++){
                printf("p%d ", queue[m]);
            }
            printf(">");
            return;
        }
    }
}