#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

volatile sig_atomic_t counter = 0;
volatile sig_atomic_t exit_ = 1;

void handle_user_1(int signum) {
  counter++;
}

void handle_user_2(int signum) {
  counter *= -1;
}

void handle_sigterm(int signum) {
  exit_ = 0;
}

int main() {
  struct sigaction user_1;
  memset(&user_1, 0, sizeof(user_1));
  user_1.sa_handler = handle_user_1;
  user_1.sa_flags = SA_RESTART;
  sigaction(SIGUSR1, &user_1, NULL);

  struct sigaction user_2;
  memset(&user_2, 0, sizeof(user_2));
  user_2.sa_handler = handle_user_2;
  user_2.sa_flags = SA_RESTART;
  sigaction(SIGUSR2, &user_2, NULL);

  struct sigaction action_term;
  memset(&action_term, 0, sizeof(action_term));
  action_term.sa_handler = handle_sigterm;
  action_term.sa_flags = SA_RESTART;
  sigaction(SIGTERM, &action_term, NULL);

  printf("%d\n", getpid());
  fflush(stdout);
  scanf("%d", &counter);
  while (exit_) {
    pause();
    printf("%d ", counter);
    fflush(stdout);
  }
  return 0;
}
