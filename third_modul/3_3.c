#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[]){
  int fds_pair[2];
  int fds_pair_c[2];
  pipe(fds_pair);

  fds_pair_c[0] = 2;
  for (int i = 1; i<argc; ++i){
    pid_t pid = fork();
    char* cmd = argv[i];

    if (pid == 0){
      if (i!=1){
        dup2(fds_pair_c[0], 0);
	close(fds_pair_c[0]);
      }

      dup2(fds_pair[1], 1);
      close(fds_pair[0]);

      execlp(cmd, cmd, NULL);
    }
    else{
      waitpid(pid, 0, 0);

      close(fds_pair[1]);
      fds_pair_c[0] = fds_pair[0];
      close(fds_pair[1]);

      pipe(fds_pair);

      if (i == argc - 2){
        fds_pair[1] = 1;
      }
    }
    waitpid(pid, 0, 0);
  }
  return 0;
}
