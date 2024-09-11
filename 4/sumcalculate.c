#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    int pid, n, oddsum = 0, evensum=0;
    printf("Enter the value of n:\n");
    scanf("$d", &n);

    pid=fork();
    if(pid<0){
        printf("Fork failed");
        return 1;
    }
    else if(pid==0){
        for(int i = 1; i<=n;i++){
            if(i%2!=0){
                oddsum+=i;
            }
        }
        printf("Sum of odd numbers: %d\n", oddsum);
        _exit(0);
    }
    else{
        wait(NULL);
        for(int i=1;i<=n;i++){
            if(i%2==0){
                evensum+=i;
            }
        }
    }

}