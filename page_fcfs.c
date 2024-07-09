#include<stdio.h>

void main(){
    int frames, len, fcfs=0, j, faults=0;
    printf("Enter number of frames: ");
    scanf("%d", &frames);
    printf("Enter Reference string length: ");
    scanf("%d", &len);
    int string[len], frame[frames];

    for(int i=0; i<len; i++){
        scanf("%d", &string[i]);
    }

    for(int i=0; i<frames; i++){
        frame[i] = -1;
    }

    printf("\nString\t|  Frames |\n");
    printf("-----------------------\n");
    for(int i=0; i<len; i++){
        int hit=0;
        printf("   %d\t|", string[i]);
        //already present
        for(j=0; j<frames; j++){
            if(frame[j]==string[i]){
                hit=1;
                break;
            }
        }

        if(j==frames){
            for(j=0; j<frames; j++){
                if(frame[j]==-1){
                    faults++;
                    frame[j] = string[i];
                    hit=0;
                    break;
                }
            }
            if(j==frames){
                faults++;
                frame[fcfs] = string[i];
                fcfs = (fcfs+1)%frames;
                hit=0;
            }
        }
        for(j=0; j<frames; j++){
            if(frame[j]==-1)
                printf(" - ");
            else
                printf(" %d ", frame[j]);
        }
        if(hit==1)
            printf("| HIT");
        else
            printf("| MISS");
        printf("\n");
    }
    printf("page faults: %d", faults);
}