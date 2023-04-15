#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#include<inttypes.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    char* name = argv[1];
    int file = open(name, O_RDONLY);
    if (file == -1) {
        return 0;
    }
    struct stat st;
    int got = fstat(file, &st);
    if ((got == -1)||(st.st_size==0)) {
        return 0;
    }
    char* mem_ptr = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, file, 0);
    int val = 0;
    uint32_t curr_ptr = -10;
    while (curr_ptr != 0) {
        if (curr_ptr == -10) {
            curr_ptr = 0;
        }
        val = *(int*)(mem_ptr + curr_ptr);
        printf("%d ", val);
        curr_ptr = *(uint32_t*)(mem_ptr + curr_ptr + sizeof(int));
    }
    munmap(mem_ptr, st.st_size);
    printf("\n");
    return 0;
}
