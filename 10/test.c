#include <stdio.h>

#define n 5
#define m 3

int allocation[n][m] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};
int max[n][m] = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};
int available[m] = {3, 3, 2};

void calculate_need(int need[n][m]){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

}

void is_safe(){
    int need[n][m];
    calculate_need(need);
    int work[m];
    for (int i=0;i<m;i++){
        work[i] = available[i];
    }

    int finish[n] = {0};
    int safe_sequence[n];
    int count= 0;

    while(count < n){
        int found = 0 ;
        for(int p=0;p<n;p++){
            int j;
            for(int j=0;j<m;j++){
                if( need[p][j]>work){
                    break;
                }
                if(j==m){
                    for(int k=0;k<m;k++){
                        work[k]+=allocation[p][k];
                    }
                    safe_sequence[count++]=p;
                    finish[p] = 1;
                    found = 1;
                }
            }
        }
         if (!found) {
            printf("System is not in a safe state.\n");
            return 0;
        }
    }
 printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", safe_sequence[i]);
    }
    printf("\n");
    return 1;

}

int main(){
    is_safe();
    return 0;
}