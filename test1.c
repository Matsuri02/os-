#include<unistd.h>
#include<sys/syscall.h>
#include<stdio.h>
int main()
{
       long a;
       a=syscall(451,2,3);
       printf("a=%ld\n",a);
       a=syscall(451,5,67);
       printf("a=%ld\n",a);
       a=syscall(452,2,3,4);
       printf("a=%ld\n",a);
       a=syscall(452,23,14,53);
       printf("a=%ld\n",a);
       return 0;
}
