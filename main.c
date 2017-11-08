#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>

static void sighandler(int signo) {
  switch (signo) {
  case SIGINT: {
      int log_fd = open("crash_log.txt", O_WRONLY | O_APPEND | O_CREAT, 0777);

      char message[256];
      sprintf(message, "This process, PID %ld, just crashed because of a SIGINT!\n", (long)getpid());

      write(log_fd, message, strlen(message) + 1);

      exit(1);
      break;
  }
  case SIGUSR1: {
    printf("PPID: %ld\n", (long)getppid());
    break; 
  }
  }
}

int main() {
  signal(SIGINT, sighandler);
  signal(SIGUSR1, sighandler);

  while (1) {
    printf("PID: %ld\n", (long)getpid());
    sleep(1);
  }

  return 0;
}
