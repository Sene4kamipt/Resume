#include <fcntl.h>
#include <inttypes.h>
#include <libgen.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int get_number(int i, int j, int N)
{
    if (j==i){
        if(j<N-j-1){
            return N*N-(N-2*j)*(N-2*j)+1;
        }
        else{
            return N*N-(i-N+i+2)*(i-N+i+2)+2*(i-(N-i-1))+1;
        }    
    }    
    if (i>j){
    	if (N-i-1>j){
    	    if (N-j-1>j){
                int y = N*N -(N-2*(j+1))*(N-2*(j+1))+1;
                //printf("%d ", y);
                y+=j-i ;
                //printf("%d ", y);
                //y+=i-(N-j-1);
                //printf("%d ", j);
                return y;

            }
            else{
                int y = N*N - 4*j*j;
                y+= 2*j-N+i-N+j;
                return y;    
            }
    	}
        else{
            if(N-j-1>N-i-1){
                int y = N*N - (N-2*(N-i-1+1))*(N-2*(N-i-1+1))+1;
               // printf("%d ", y);
                y-=i-(N-i-1);
                y-=j-(N-i-1);
                
                return y;
            }
            else{
                int y = N*N - j*j;
                y+= 2*j-N+i-N+j;
                return y;
            }
        }

    }
    else{
        if (N-i-1>i){
            if (N-j-1>i){
                int y = N*N-(N-2*i)*(N-2*i);
                y+=j-i;
                return y+1;
            }
            else{
                int y = N*N -(N-2*(N-j-1))*(N-2*(N-j-1))+1;
                //printf("%d ", y);
                y+= -N+j+j+1;
                //printf("%d ", y);
                y+=i-(N-j-1);
                //printf("%d ", j);
                return y;
             }
        }
        else{
            if(N-j-1>N-i-1){
                int y = N*N - i*i;
                y+= 2*i-N+j-N+i;
                return y;
        
            }
            else{
                int y = N*N -(N-2*(N-j-1))*(N-2*(N-j-1))+1;
                //printf("%d ", y);
                y+= -N+j+j+1;
                //printf("%d ", y);
                y+=i-(N-j-1);
                //printf("%d ", j);
                return y;

            }
        }

    }
}

int main(int argc, char* argv[])
{
    char* file_name = argv[1];
    int symb = atoi(argv[3]);
    int sz = atoi(argv[2]);
    int file_d = open(file_name, O_RDWR | O_CREAT | O_TRUNC);
    if (file_d == -1) {
        return 1;
    }
    uint64_t real_sz= (long long)sz * sz * symb + sz;
    char square[symb + 1];
    lseek(file_d, real_sz-1, SEEK_SET);
    write(file_d, "", 1);
    char* mem_ptr = mmap(NULL, real_sz, PROT_READ | PROT_WRITE, MAP_SHARED, file_d, 0);
    for (int i = 0; i < sz; ++i) {
        for (int j = 0; j < sz; ++j) {
            int len = 0;
            int value = get_number(i, j, sz);
            int val_cp = value;
	    while(val_cp){
	    	len++;
	    	val_cp/=10;
	    }
            memset(square, ' ', symb-len);
            square[symb-len] = '\0';
            sprintf(square + symb-len, "%d", value);
            memcpy(mem_ptr + i*(sz * symb + 1) + symb*j, square, symb);
        }
        memcpy(mem_ptr+i*(sz*symb+ 1) +sz*symb, "\n", 1);
    }
    msync(mem_ptr, real_sz,MS_SYNC);
    munmap(mem_ptr, real_sz);
    return 0;
}
