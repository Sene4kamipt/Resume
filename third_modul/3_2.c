#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>

int main(int argc, char* argv[]) {
  char* file_name = argv[1];
  int fds[2];
  pipe(fds);

  pid_t pid = fork();
  if (pid == 0){
    dup2(fds[1], 2);
    close(fds[1]);
    execlp("gcc", "gcc", file_name,(char *) NULL);
  }
  else{
    close(fds[1]);
    waitpid(pid, 0, 0);
  
    uint64_t number_of_errors = 0;
    uint64_t number_of_warnings = 0;
  
    char buff_1[1000];
    char buff_2[1000];
  
    char last_error_str[100];
    char last_warning_str[100];

    int len_name_file = strlen(file_name);

    FILE* file = fdopen(fds[0], "r");

    while (fscanf(file, "%s", buff_1) > 0) {
      if (strcmp(buff_1, "error:")==0) {
        int i = 0;
        while (true){
	  if (buff_2[len_name_file+1+i]==':'){
	    break;
	  }
      	  if (buff_2[len_name_file+1+i]!=last_error_str[i]){
	    number_of_errors+=1;
            for (int j=len_name_file+1; buff_2[j]!=':'; ++j){
	      last_error_str[j-len_name_file-1] = buff_2[j];
	    }
	    break;
	  }
          i+=1;
        }
      } 

      else{ 
        if (strcmp(buff_1, "warning:") == 0) {
          int i = 0;
          while (true){
            if (buff_2[len_name_file+1+i]==':'){
              break;
            }
            if (buff_2[len_name_file+1+i]!=last_warning_str[i]){
              number_of_warnings+=1;
              for (int j=len_name_file+1; buff_2[j]!=':'; ++j){
                last_warning_str[j-len_name_file-1] = buff_2[j];
              }
              break;
            }
            i+=1;
          }
        }
      }
      strncpy(buff_2, buff_1, 1000);
    }
    printf("%ld %ld\n", number_of_errors, number_of_warnings);
  }
  return 0;
}
