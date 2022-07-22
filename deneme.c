
#include <stdlib.h>
#include <stdio.h>

char *readTextInput(void)
{
  char Text_Size = 12;
  int len, character;
  char *Text;
  Text = (char *)malloc(sizeof(char) * Text_Size);
  int loop = 0;

  Text = fgets(Text, Text_Size - 1, stdin);
  long pos = ftell(stdin);

  printf("Start to iterate:\n");
  for (int i = 0; i < Text_Size - 1; i++)
  {
    if (Text[i] == '\n' && Text != EOF)
    {
      loop = 1;
      Text[Text_Size] = '\0';
      break;
    }
    else
    {
      printf("%d: %c\n", i, Text[i]);

      // new_Text = Text + Text[i];
    }
  }
  printf("\nend iterataion\n");

  if (loop != 1)
  {
    Text = (char *)realloc(Text, Text_Size + Text_Size);
    printf("here: %c\n", Text[Text_Size]);

    for (len = 10; (character = getchar()) != '\n' && character != EOF; len++)
    {
      if (len > Text_Size + Text_Size)
      {
        break;
      }
      Text[len] = character;
    }

    // fputs(Text, stdin);
    // printf("%s", Text);
    printf("#########EOF############\n");

    // fgets(Text, Text_Size * 2, stdin);
    // printf("%s", Text);

  }

  return (Text);
}