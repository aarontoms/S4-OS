#include<stdio.h>

int frames, len;

int check(int frame[], int string[], int x){
    int i, j, done=0;

    for(i=x; i<len; i++){
        for(j=0; j<frames; j++){
            if(frame[j]==string[i]){
                frame[j] = -1;
                done++;
                break;
            }
        }
        if(done==frames)
            return j;
        
    }
    for(j=0; j<frames; j++){
        if(frame[j] != -1){
            return j;
        }
    }
}

void main(){
    int optimal, j, hit=0, faults=0;

    printf("Enter number of frames: ");
    scanf("%d", &frames);
    printf("Enter reference string length: ");
    scanf("%d", &len);
    int frame[frames], string[len], copy[frames];

    printf("Reference String: "); 
    for(int i=0; i<len; i++){
        scanf("%d", &string[i]);
    }
    for(int i=0; i<frames; i++){
        frame[i] = -1;
    }

    printf("String\t|  Frames  |\n");
    printf("-----------------------\n");
    for(int i=0; i<len; i++){
        for(j=0; j<frames; j++){
            if(frame[j]==string[i]){
                hit=1;
                break;
            }
        }
        if(j==frames){
            for(j=0; j<frames; j++){
                if(frame[j]==-1){
                    hit=0;
                    frame[j] = string[i];
                    faults++;
                    break;
                }
            }
            if(j==frames){
                hit=0;
                faults++;
                for(int k=0; k<frames; k++){
                    copy[k] = frame[k];
                }
                optimal = check(copy, string, i);
                frame[optimal] = string[i];
            }
        }
        printf("  %d\t|", string[i]);
        for(int k=0; k<frames; k++){
            if(frame[k]==-1)
                printf(" - ");
            else
                printf(" %d ", frame[k]);
        }

        if(hit==0)
            printf("|  MISS\n");
        else
            printf("|  HIT\n");
    }
    printf("Page Faults: %d\n", faults);
}