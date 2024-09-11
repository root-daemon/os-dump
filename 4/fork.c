#include <stdio.h>
#include <unistd.h>

int main(){
    int a=5, b=10,pid;
    printf("Before fork a=%d b=%d \n",a,b);
    pid=vfork();

    if(pid==0){
        a=a+1;
        b=b+1;
        printf("In Child a=%d b=%d \n",a,b);
    }
    else{
        sleep(1);
        a=a-1; 
        b=b-1;
        printf("In paternt a=%d b=%d \n",a,b);

        return 0;
    }
}