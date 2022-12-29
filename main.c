#include <stdio.h>
#include <stdlib.h>

#define LEN 32

char buffer[LEN];

int main(int argc, char **args)
{
  int a     = 5;
  int b     = 7;
  int bluat = 18;

  int c = 5;
  if (argc != 2)
    {
      fprintf(stderr,
              "please pass a file name as an argument (it may not exist)\n");
      exit(1);
    }
  unsigned int count;
  FILE *handle = fopen(args[1], "r");
  if (handle)
    {
      fgets(buffer, LEN, handle);
      if (buffer[0] == 0)
        count = 1; // we start on row one
      else
        {
          char *tmp = 0;
          count     = strtol(buffer, &tmp, 0);
          if (tmp == buffer)
            {
              fprintf(stderr, "not a valid int. smh\n");
            }
        }
    }
  fclose(handle);
  fopen(args[1], "w");

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
  fprintf(handle, "%u\n", count);
  fclose(handle);
  return 0;
}
