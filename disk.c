#include<stdio.h>

int track[20];
int tracks, head, lower_bound=0, upper_bound=199;

void fcfs(){
    int dist=0;

    printf("Service Order: %d", track[0]);
    for(int i=1; i<tracks; i++){
        printf(" %d", track[i]);
        if(track[i] > track[i-1])
            dist += track[i]-track[i-1];
        else
            dist += track[i-1]-track[i];
    }

    printf("\nDistance: %d\n", dist);
}

int sort(){
    for(int i=0; i<tracks-1; i++){
        for(int j=0; j<tracks-i-1; j++){
            if(track[j] > track[j+1]){
                int temp = track[j];
                track[j] = track[j+1];
                track[j+1] = temp;
            }
        }
    }

    for(int i=0; i<tracks; i++){
        if(track[i]==head)
            return i;
    }
}

void scan(){
    int dist=0;
    int hed = sort();

    printf("Service Order: %d", track[hed]);
    for(int i=hed+1; i<tracks; i++){
        dist += track[i] - track[i-1];
        printf(" %d", track[i]);
    }
    dist += upper_bound - track[tracks-1];
    printf(" %d", upper_bound);
    dist += upper_bound - track[hed-1];
    printf(" %d", track[hed-1]);
    for(int i=hed-2; i>=0; i--){
        printf(" %d", track[i]);
        dist += track[i+1] - track[i];
    }

    printf("\nDistance: %d\n", dist);
}

void cscan(){
    int dist=0;
    int hed = sort();

    printf("Service Order: %d", track[hed]);
    for(int i=hed+1; i<tracks; i++){
        printf(" %d", track[i]);
        dist += track[i] - track[i-1];
    }
    dist += upper_bound - track[tracks-1];
    dist += upper_bound - lower_bound;
    dist += track[0] - lower_bound;
    printf(" %d", upper_bound);
    printf(" %d", lower_bound);
    printf(" %d", track[0]);
    for(int i=1; i<hed; i++){
        printf(" %d", track[i]);
        dist += track[i] - track[i-1];
    }
    printf("\nDistance: %d\n", dist);
}

void main(){
    int ch;

    printf("Enter number of tracks: ");
    scanf("%d", &tracks);
    printf("Enter the tracks: ");
    for(int i=0; i<tracks; i++){
        scanf("%d", &track[i+1]);
    }
    printf("Enter head: ");
    scanf("%d", &head);
    track[0] = head;
    tracks++;

    do{
        printf("\n---MENU---\n 1. FCFS\n 2. Scan\n 3. C-Scan\nEnter choice: ");
        scanf("%d", &ch);
        switch(ch){
        case 1:
            fcfs();
            break;
        case 2:
            scan();
            break;
        case 3:
            cscan();
            break;
        }
    }while(ch!=4);
}