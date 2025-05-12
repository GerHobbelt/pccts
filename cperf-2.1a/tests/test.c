#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
  char buf[256];
  int ef = (argc > 1 && !strcmp(argv[1], "-v"));

  while (!feof(stdin))
  {
    buf[0] = 0;
    fgets(buf,sizeof(buf), stdin);
    buf[sizeof(buf)-1] = 0;
    /* strip terminating \n */
    if (strchr(buf, '\n'))
      strchr(buf, '\n')[0] = 0;
    if (buf[0] == 0)
      continue;
    
    /* feed string to hash routine: should find a match! */
#if 0
    printf("testing keyword [%s]\n", buf);
#endif
    if (!in_word_set(buf, strlen(buf)))
    {
      if (!ef)
        exit(EXIT_FAILURE);
    }
    else if (ef)
    {
      printf("match: [%s]\n", buf);
    }
  }
  return EXIT_SUCCESS;
}
