#include <sys/signalfd.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char* argv[]) {
  FILE* fd[argc - 1];
  //printf("%d\n", getpid());
  //fflush(stdout);
  for(int i = 0; i < argc-1; i++) {
    fd[i] = fopen(argv[i+1], "r");
  }
  sigset_t set_block, set_file;
  sigfillset(&set_block);
  sigprocmask(SIG_BLOCK, &set_block, NULL);
  sigemptyset(&set_file);
  for (int i=SIGRTMIN; i<argc+SIGRTMIN; ++i){
    sigaddset(&set_file, i);
  }
  int curr_fd = signalfd(-1, &set_file, 0);
  struct signalfd_siginfo sig_fd;
  char outpu[1000];
  bool flag = true;
  while(flag){
    read(curr_fd, &sig_fd, sizeof(sig_fd));
    if(sig_fd.ssi_signo == SIGRTMIN){
      flag = false;
    }
    else{
      fgets(outpu, sizeof(outpu), fd[sig_fd.ssi_signo-SIGRTMIN-1]);
      fputs(outpu, stdout);
      fflush(stdout);
    }
  }
}
