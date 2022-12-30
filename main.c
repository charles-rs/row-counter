#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#define LEN 32

char buffer[LEN];

unsigned int count = 1;
FILE *handle       = 0;

void stop()
{
  if (handle)
    {
      fprintf(handle, "%u\n", count);
      fclose(handle);
      handle = 0;
    }
}

void sig_handler(int signo)
{
  if (signo == SIGINT)
    {
      stop();
      exit(0);
    }
}

int main(int argc, char **args)
{
  signal(SIGINT, sig_handler);
  if (argc != 2)
    {
      fprintf(stderr,
              "please pass a file name as an argument (it may not exist)\n");
      exit(1);
    }
  handle = fopen(args[1], "r");
  if (handle)
    {
      fgets(buffer, LEN, handle);
      if (buffer[0] != 0)
        {
          char *tmp = 0;
          count     = strtol(buffer, &tmp, 0);
          if (tmp == buffer)
            {
              fprintf(stderr, "not a valid int. smh\n");
            }
        }
      fclose(handle);
    }
  handle = fopen(args[1], "w");

  printf("welcome. don't enter commands longer than %d in order to ensure "
         "memory safety\n",
         LEN);

  while (1)
    {
      printf("You are on row %u\n", count);
      fgets(buffer, LEN, stdin);
      if (buffer[0] == '\n')
        ++count;
      else if (buffer[0] == 'q' && buffer[1] == '\n')
        break;
      else
        puts("please enter a valid command. (blank to increment rows)");
    }
  stop();
  return 0;
}
