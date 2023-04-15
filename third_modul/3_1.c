#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

void solve(const char* cmd1, const char* cmd2){
  int pipefd[2];
  pipe(pipefd);

  pid_t pid_1 = fork();
  if ( 0== pid_1){
    dup2(pipefd[1], 1);
    close(pipefd[1]);
    close(pipefd[0]);
    execlp(cmd1, cmd1, (char*)NULL);
  }
  else{
    close(pipefd[1]);
    pid_t pid_2 = fork();
    if (0 == pid_2){
      dup2(pipefd[0], 0);
      close(pipefd[0]);
      execlp(cmd2, cmd2, (char*)NULL);
    }
    else{
      close(pipefd[0]);
      waitpid(pid_1, 0, 0);
      waitpid(pid_2, 0, 0);
    }
  }
}

int main(int argc, char **argv){
  solve(argv[1], argv[2]);
  return 0;
}
