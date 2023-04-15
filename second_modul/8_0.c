#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

const int MAX_BUFF_SIZE = 4096;

int main(int argc, char* argv[]){
    char buffer[MAX_BUFF_SIZE];
    char digits_buff[MAX_BUFF_SIZE];
    char other_buff[MAX_BUFF_SIZE];
    int exit_code = 0;
    int in = open(argv[1], O_RDONLY);
    int out_other = open(argv[3], O_WRONLY | O_CREAT, 0644);
    int out_digits = open(argv[2], O_WRONLY | O_CREAT, 0644);
    if (-1 == in){
        exit_code =1;
        goto finally;
    }
    if (-1== out_digits || -1 == out_other){
        exit_code = 2;
        goto finally;
    }
    int input_read;
    int digits_read;
    int other_read;
    int out =0;
    while (1){
        input_read = read(in, buffer, MAX_BUFF_SIZE);
        if (input_read == 0){
            break;
        }
        if (input_read ==-1){
            exit_code =3;
            goto finally;
        }
        digits_read =0;
        other_read = 0;
        for (int idx=0; idx<input_read;++idx){
            if (buffer[idx]>='0' && buffer[idx]<='9'){
                digits_buff[digits_read] = buffer[idx];
                ++digits_read;
            }else{
                other_buff[other_read] = buffer[idx];
                ++other_read;
            }
        }
        while ((out = write(out_digits, digits_buff+out, digits_read - out))!=0){
            if (out == -1){
                exit_code = 3;
                break;
            }
        }
        while ((out = write(out_other, other_buff+out, other_read - out))!=0){
            if (out == -1){
                exit_code = 3;
                break;
            }
        }
        goto finally;
    }
finally:
    close(in);
    close(out_digits);
    close(out_other);
    return exit_code;
}
