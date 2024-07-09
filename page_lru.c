#include<stdio.h>

int frames;
int check(int frame[], int string[], int x){
    int done=0, i, j;
    
    for(i=x; i>=0; i--){
        for(j=0; j<frames; j++){
            if(string[i]==frame[j]){
                frame[j]=-1;
                done++;
                break;
            }
        }
        if(done==frames)
            return j;
    }
}

void main(){
    int len, j, hit=0, lru=0, faults=0;
    printf("Enter the number of frames: ");
    scanf("%d", &frames);
    printf("Enter String reference length: ");
    scanf("%d", &len);
    int frame[frames], string[len];
    printf("Reference String: ");
    for(int i=0; i<len; i++){
        scanf("%d", &string[i]);
    }
    for(int i=0; i<frames; i++){
        frame[i] = -1;
    }

    printf("\nString\t|  Frames |\n");
    printf("-----------------------\n");
    for(int i=0; i<len; i++){
        printf("   %d\t|", string[i]);
        for(j=0; j<frames; j++){
            if(frame[j]==string[i]){
                hit=1;
                break;
            }
        }
        if(j==frames){
            for(j=0; j<frames; j++){
                if(frame[j]==-1){
                    // printf("here ");
                    frame[j] = string[i];
                    hit=0;
                    faults++;
                    break;
                }
            }
            if(j==frames){
                // find least recently used
                int copy[frames];
                for(int c=0; c<frames; c++){
                    copy[c] = frame[c];
                }
                lru = check(copy, string, i);
                // printf("remove %d", lru);
                frame[lru] = string[i];
                hit=0;
                faults++;
            }
        }

        for(int k=0; k<frames; k++){
            if(frame[k]>=0)
                printf(" %d ", frame[k]);
            else
                printf(" - ");
        }
        if(hit==0)
            printf("| MISS\n");
        else
            printf("| HIT\n");
    }
    printf("page fault: %d", faults);
}