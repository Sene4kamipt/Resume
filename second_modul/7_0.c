#include <unistd.h>
#include <sys/syscall.h>
 
long syscall(long number, ...);
 
void _start(){
    char input[100];
    int n;
    while ((n = syscall(SYS_read, 0, input, 100)) > 0) {
        syscall(SYS_write, 1, input, n);
    }
    syscall(SYS_exit, 0);
}
