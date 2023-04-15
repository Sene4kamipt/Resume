#include <unistd.h>
#include <sys/syscall.h>


long syscall(long number, ...);

void _start(){
    const char* hello = "Hello, World!\n";
    syscall(SYS_write, 1, hello, 14);
    syscall(SYS_exit, 0);
}
