#include <windows.h>
#include <stdio.h>
#include <stdint.h>

int main(int args, char* argv[]) {
	HANDLE in = CreateFileA(argv[1], GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);
    if(in<0){
        return 1;
    }
    int curr_value;
    uint32_t next_pointer;
    DWORD flag = 0;
	ReadFile(in, &curr_value, 4, &flag, NULL);
    if(flag==0){
		return 0;
    }
    ReadFile(in, &next_pointer, 4, &flag, NULL);
	while(next_pointer>0){
        printf("%d\n", curr_value);
        SetFilePointer(in, next_pointer, NULL, FILE_BEGIN);
		ReadFile(in, &curr_value, 4, &flag, NULL);
		ReadFile(in, &next_pointer, 4, &flag, NULL);	
    }
    printf("%d\n", curr_value);
    return 0;
    
}
