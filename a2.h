//-----------------------------------------------------------------------------
// a2.h
//
// This file contains all the functions used in a2.c
//
//
// Author: 11929652
//-----------------------------------------------------------------------------
//

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#define MAX_STARTING_CHAR_INPUT 100

//
/// This function reads the input from the stdin and changes the inputted
/// text size if it wasn't enough. It also saves the inputted text into a
/// dynamically allocated array text_buffer and returns the pointer to this
/// array
///
/// @param text_size The starting size for the memory allocation of our Text.
///        The paramater is dereferenced so that we change the value if the
///        starting size wasn't enough.
///
/// @return char *text_buffer
//
char *readTextInput(int *text_size)
{
  int len, character;
  int is_input_short = 0;

  char *text_buffer;
  text_buffer = (char *)malloc(*text_size * sizeof(char) + 5);
  if (text_buffer == NULL)
  {
    return text_buffer;
  }
  text_buffer = fgets(text_buffer, *text_size, stdin);

  // if there is an enter in the input its shorter than 100 else we alloc memory fore every other char
  for (int i = 0; i < *text_size; i++)
  {
    if (text_buffer[i] == '\n')
    {
      is_input_short = 1;
      *text_size = i;
    }
  }
  if (is_input_short == 0)
  {
    for (len = MAX_STARTING_CHAR_INPUT - 1; (character = getchar()) != '\n' && character != EOF; len++)
    {
      char *tmp = realloc(text_buffer, len + *text_size);
      if (tmp == NULL)
      {
        return tmp;
      }
      text_buffer = tmp;

      text_buffer[len] = character;
    }
    text_buffer[len] = '\0';
    *text_size = len;
  }
  return (text_buffer);
}
//
/// This function creates a 2d array
///
/// @param row rows of array
///
/// @param column column length of array
///
/// @return char** pointer to 2d array
//
char **get2dArray(int row, int column, int sentence_size)
{
  char **arr_ptr = (char **)calloc(row, sizeof(char *));
  for (int i = 0; i < row; i++)
  {
    // printf("%d", sentence_sizes[i]);

    arr_ptr[i] = (char *)calloc(column, sentence_size + 1);
    // printf("%lu", sizeof(char *));
  }
  return arr_ptr;
}
//
/// This function fills our 2d array with the sentences from our text input using the pointers
/// that we stored in our sentence_ptrs array
///
/// @param sentence_total (int *) the total of sentences
///
/// @param sentence_ptrs (char **) array of ptrs to the first letters of the sentences beginninngs in out text
///
/// @param sentence_sizes (int[]) array that contains our sentence sizes
///
/// @param sentences_seperated_2d (char **) the 2d array we want to fill
///
/// @return void
//
void fill2dArray(int *sentence_total, char **sentence_ptrs, int sentence_sizes[], char **sentences_seperated_2d)
{
  for (int row = 0; row < *sentence_total; row++)
  {
    char **ptr = &sentence_ptrs[row];
    int size_limit = sentence_sizes[row];
    for (int column = 0; column < size_limit; column++)
    {
      int sizes = sentence_sizes[row] - 1; //for space at end
      if (column <= sizes)
      {
        sentences_seperated_2d[row][column] = *(*ptr + column);
      }
    }
  }
}
//
/// This function swaps two 2d arrays
///
/// @param array_one (char ***) first array
///
/// @param array_two  (char ***) second array
///
/// @return void
//
void swap2dArray(char ***array_one, char ***array_two)
{
  char **tmp = *array_one;
  *array_one = *array_two;
  *array_two = tmp;
}
//
/// This function iterates over the given text and iterates over it until
/// the given size is reached. If a punctuation is iterated over we increment
/// the sentence_total.
///
/// @param text (char *) The text we want to iterate over
///
/// @param text_size (int) The size of the text that user wants to input.
///
/// @return int sentence_total
//
int getSentenceTotal(char *text, int text_size)
{
  int sentence_total = 0;

  for (int i = 0; i < text_size; i++)
  {
    if (text[i] == '.' || text[i] == '!' || text[i] == '?')
    {
      sentence_total++;
    }
  }
  return sentence_total;
}
//
/// This function saves the addresses of pointers to the first words of a sentence
/// in a given text to a dynamically created array of pointers. Returns the array
/// of pointers.
///
/// @param text (char*) The text we want to iterate over
///
/// @param text_size (int) The size of the text that user wants to input.
///
/// @param sentence_total (int* ) The total amount of sentences the text contains.
///
/// @param vector (char** ) to free the vector if it goes wrong.
///
/// @return int sentence_ptrs
//
char **getSentencePointers(char **sentence_ptrs, char *text, int text_size, int *sentence_total)
{

  int ptr_to_char = 0;
  int y = 0;
  char next_char;

  //account for space in the beginning of text
  if (text[0] == ' ')
  {
    do
    {
      y++;
      next_char = text[y];
    } while (next_char == ' ' && y < text_size);
    sentence_ptrs[ptr_to_char] = &text[y];
    y = 0;
  }
  else
  {
    sentence_ptrs[0] = &text[0];
  }

  for (int i = 0; i < text_size; i++)
  {
    if ((text[i] == '.' || text[i] == '!' || text[i] == '?') && (ptr_to_char != *sentence_total - 1))
    {
      // check if there is a space after the punctuation
      if (text[i + 1] != ' ')
      {
        ptr_to_char++;
        sentence_ptrs[ptr_to_char] = &text[i + 1];
      }
      else
      {
        do
        {
          i++;
          next_char = text[i];
        } while (next_char == ' ' && i < text_size);
        ptr_to_char++;
        sentence_ptrs[ptr_to_char] = &text[i];
      }
    }
  }

  if (text[text_size - 1] != '.' && text[text_size - 1] != '!' && text[text_size - 1] != '?')
  {
    printf("Der Text endet ohne Satzzeichen!\n");
    *sentence_ptrs = NULL;
  }

  return sentence_ptrs;
}

//
/// This function concats the sentences if th first user is bigger than the second one
/// also adjusts the size array accordingly
///
/// @param first_sentence_to_merge no of first sentence seleceted to be merged
///
/// @param second_sentence_to_merge no of second sentence seleceted to be merged
///
/// @param size_of_first_sentence size of first sentence seleceted to be merged
///
/// @param new_sentence_size what the length of the resulting concatted string is/will be
///
/// @param new_sentences_seperated The new resized 2d array we store the sentences to
///
/// @param temp_sentences_seperated The 2d array that has all the sentences
///
/// @return void
//
void concatFirstBigger(int first_sentence_to_merge, int second_sentence_to_merge, int size_of_first_sentence, int new_sentence_size, char **new_sentences_seperated, char **temp_sentences_seperated, int *ptr_sentence_sizes, int sentence_total)
{
  int concat_sentence_index = 0;
  int und = 0;
  int second_sentence_to_merge_idx = second_sentence_to_merge;

  for (int size_of_first_sentence_idx = size_of_first_sentence; size_of_first_sentence_idx < new_sentence_size; size_of_first_sentence_idx++)
  {

    if (und == 0)
    {
      new_sentences_seperated[first_sentence_to_merge][size_of_first_sentence_idx - 1] = ' ';

      new_sentences_seperated[first_sentence_to_merge][size_of_first_sentence_idx] = 'u';
      size_of_first_sentence_idx++;

      new_sentences_seperated[first_sentence_to_merge][size_of_first_sentence_idx] = 'n';
      size_of_first_sentence_idx++;

      new_sentences_seperated[first_sentence_to_merge][size_of_first_sentence_idx] = 'd';
      size_of_first_sentence_idx++;

      new_sentences_seperated[first_sentence_to_merge][size_of_first_sentence_idx] = ' ';
      size_of_first_sentence_idx++;
      new_sentences_seperated[first_sentence_to_merge][size_of_first_sentence_idx] = tolower(new_sentences_seperated[first_sentence_to_merge][size_of_first_sentence_idx]);
      und++;
    }
    new_sentences_seperated[first_sentence_to_merge][size_of_first_sentence_idx] = temp_sentences_seperated[second_sentence_to_merge][concat_sentence_index];
    concat_sentence_index++;
  }
  //resize
  for (; second_sentence_to_merge_idx < sentence_total; second_sentence_to_merge_idx++)
  {
    *(ptr_sentence_sizes + second_sentence_to_merge_idx) = *(ptr_sentence_sizes + second_sentence_to_merge_idx + 1);
  }
  *(ptr_sentence_sizes + first_sentence_to_merge) = new_sentence_size;
}
//
/// This function concats the sentences if th second user is bigger than the first one
/// also adjusts the size array accordingly
///
/// @param first_sentence_to_merge no of first sentence seleceted to be merged
///
/// @param second_sentence_to_merge no of second sentence seleceted to be merged
///
/// @param size_of_first_sentence size of first sentence seleceted to be merged
///
/// @param new_sentence_size what the length of the resulting concatted string is/will be
///
/// @param new_sentences_seperated The new resized 2d array we store the sentences to
///
/// @param temp_sentences_seperated The 2d array that has all the sentences
///
/// @return void
//
void concatFirstLower(int first_sentence_to_merge, int second_sentence_to_merge, int size_of_first_sentence, int new_sentence_size, char **new_sentences_seperated, char **temp_sentences_seperated, int *ptr_sentence_sizes, int sentence_total)
{
  int concat_sentence_index = 0;
  int und = 0;
  int second_sentence_to_merge_idx = second_sentence_to_merge;

  for (int size_of_first_sentence_idx = size_of_first_sentence; size_of_first_sentence_idx < new_sentence_size; size_of_first_sentence_idx++)
  {

    if (und == 0)
    {
      // printf("\n1:%d smaller 2:%d \n", first_sentence_to_merge, second_sentence_to_merge);
      // printf("\nmerging at:%d, %d \n", first_sentence_to_merge, x - 1);
      // printf("\nfirst SENTENCE SIZE%d\n", size_of_first_sentence);

      new_sentences_seperated[first_sentence_to_merge - 1][size_of_first_sentence_idx - 1] = ' ';

      new_sentences_seperated[first_sentence_to_merge - 1][size_of_first_sentence_idx] = 'u';
      size_of_first_sentence_idx++;

      new_sentences_seperated[first_sentence_to_merge - 1][size_of_first_sentence_idx] = 'n';
      size_of_first_sentence_idx++;

      new_sentences_seperated[first_sentence_to_merge - 1][size_of_first_sentence_idx] = 'd';
      size_of_first_sentence_idx++;

      new_sentences_seperated[first_sentence_to_merge - 1][size_of_first_sentence_idx] = ' ';
      size_of_first_sentence_idx++;
      new_sentences_seperated[first_sentence_to_merge - 1][size_of_first_sentence_idx] = tolower(new_sentences_seperated[second_sentence_to_merge][size_of_first_sentence_idx]);
      und++;
    }
    new_sentences_seperated[first_sentence_to_merge - 1][size_of_first_sentence_idx] = temp_sentences_seperated[second_sentence_to_merge][concat_sentence_index];
    concat_sentence_index++;
  }
  for (; second_sentence_to_merge_idx < sentence_total; second_sentence_to_merge_idx++)
  {

    *(ptr_sentence_sizes + second_sentence_to_merge_idx) = *(ptr_sentence_sizes + second_sentence_to_merge_idx + 1);
  }
  *(ptr_sentence_sizes + first_sentence_to_merge - 1) = new_sentence_size;
}

//
/// This function concats the sentences if th first user is bigger than the second one
///
/// @param sentence_sizes The array that contains the sizes
///
/// @param sentence_total The total no of sentences
///
/// @return int biggest_sentence
///
//

int getBiggestSentence(int sentence_sizes[], int *sentence_total)
{
  int biggest_sentence = 0;
  for (int i = 0; i < *sentence_total; i++)
  {
    if (biggest_sentence < sentence_sizes[i])
    {
      biggest_sentence = sentence_sizes[i];
    }
  }
  return biggest_sentence;
}

//
/// This function iterates over a given array and sets every element to 0
///
/// @param size The size of the array
///
/// @param ptr_to_array The pointer to an array
///
/// @return void
//
void initArrayNull(int size, int *ptr_to_array)
{
  for (int i = 0; i < size; i++)
  {
    *(ptr_to_array + i) = 0;
  }
}
//
/// This function iterates over the text that contains sentences.
/// It counts every character of every sentence the text contains
/// and saves it to the array that ptr_sentence_sizes points to.
///
/// @param ptr_sentence_sizes pointer to the array that contains the
///                           sizes for each sentence
///
/// @param text The text that contains the sentences.
///
/// @param text_size The size of the text parameter
///
/// @return void
//
int countSentenceChars(int *ptr_sentence_sizes, char text[], int text_size)
{
  int next_sentence = 0;

  for (int i = 0; i < text_size; i++)
  {
    *(ptr_sentence_sizes + next_sentence) += 1;

    if (text[i] == '.' || text[i] == '!' || text[i] == '?')
    {

      next_sentence += 1;
      if (text[i + 1] == ' ' && i != text_size - 1)
      {
        *(ptr_sentence_sizes + next_sentence) -= 1;
      }
    }
  }

  //offset of starting spaces

  for (int i = 0; text[i] == ' '; i++)
  {
    if (text[i] == ' ')
    {
      *ptr_sentence_sizes -= 1;
    }
  }

  if (next_sentence == 0)
  {
    printf("Kein Satz gefunden!\n");
    return 1;
  }
  return 0;
}
//
/// This function gets all letters(+punctuation) of a text
///
/// @param text The text we want to iterate over
///
/// @param text_size The size of the text that user wants to input.
///
/// @param sentence_symbols_total The sentence symbols total count.
///
/// @return int sentence_letters_total
//
int getSentenceSymbols(char *text, int text_size, int sentence_symbols_total)
{
  for (int i = 0; i < text_size; i++)
  {
    if (text[i] != ' ' && text[i] != '\0' && text[i] != '\n')
    {
      sentence_symbols_total++;
    }
  }
  return sentence_symbols_total;
}
//
/// This function gets all letters of a text
///
/// @param text The text we want to iterate over
///
/// @param text_size The size of the text that user wants to input.
///
/// @return int sentence_letters_total
//
int getSentenceLetters(char *text, int text_size, int sentence_letters_total)
{
  for (int i = 0; i < text_size; i++)
  {
    if (text[i] >= 'A' && text[i] <= 'z' && ispunct(text[i]) == 0) //(text[i] != ' ' && text[i] != '\0' && text[i] != '\n' && ispunct(text[i]) == 0)
    {
      sentence_letters_total++;
    }
  }
  return sentence_letters_total;
}
//
/// This function gets all uppercase words of a text
///
/// @param text The text we want to iterate over
///
/// @param text_size The size of the text that user wants to input.
///
/// @return int sentence_letters_total
//
int getSentenceUpperCase(char *text, int text_size, int sentence_upper_total)
{
  for (int i = 0; i < text_size; i++)
  {
    if (isupper(text[i]))
    {
      sentence_upper_total++;
    }
  }
  return sentence_upper_total;
}
//
/// This function gets all lowercase words of a text
///
/// @param text The text we want to iterate over
///
/// @param text_size The size of the text that user wants to input.
///
/// @return int sentence_letters_total
//
int getSentenceLowerCase(char *text, int text_size, int sentence_lower_total)
{
  for (int i = 0; i < text_size; i++)
  {
    if (islower(text[i]))
    {
      sentence_lower_total++;
    }
  }
  return sentence_lower_total;
}
//
/// This function cleans the standart input buffer
///
/// @param void
///
//
void clean_stdin(void)
{
  int c;
  do
  {
    c = getchar();
  } while (c != '\n' && c != EOF);
}
//
/// This function is for the text statistik
///
/// @param text
///
/// @param text_size
///
/// @param sentence_total
///
/// @param sentence_letters_total
///
/// @param sentence_symbols_total
///
/// @param sentence_lower_total
///
/// @param sentence_upper_total
///
//
void getTextStatistik(char text[], int text_size, int *sentence_total, int sentence_letters_total, int sentence_symbols_total, int sentence_lower_total, int sentence_upper_total)
{
  int sentence_letters = getSentenceLetters(text, text_size, sentence_letters_total);
  int sentence_symbols = getSentenceSymbols(text, text_size, sentence_symbols_total);
  int sentence_lower = getSentenceLowerCase(text, text_size, sentence_lower_total);
  int sentence_upper = getSentenceUpperCase(text, text_size, sentence_upper_total);
  printf("Text Statistik:\n");
  printf("%d Sätze, %d Zeichen\n", *sentence_total, sentence_symbols);
  printf("%d Buchstaben (%d Großbuchstaben, %d Kleinbuchstaben)\n", sentence_letters, sentence_upper, sentence_lower);
}
//
/// This function is for the Text mit Zeilennummer ausgeben
///
/// @param sentence_total
///
/// @param sentences_seperated_2d
///
//
void getSentencesWithNumber(int *sentence_total, char **sentences_seperated_2d)
{
  printf(" Nr. | Satz\n-----+----------------------------------------\n");
  for (int i = 0; i < *sentence_total; i++)
  {
    printf("%4d | %s\n", i + 1, sentences_seperated_2d[i]);
  }
}
//
/// This function is for the Text ohne Zeilennummer ausgeben
///
/// @param sentence_total
///
/// @param sentences_seperated_2d
///
//
void getText(int *sentence_total, char **sentences_seperated_2d)
{
  printf("Text:\n");
  for (int i = 0; i < *sentence_total; i++)
  {
    printf("%s ", sentences_seperated_2d[i]);
  }
  printf("\n");
}
//
/// This function is for the input
///
/// @param sentence_total
///
/// @param sentences_seperated_2d
///
//
int getInput(char text[], int input, int sentence_total)
{
  int wrong_input = 0;
  do
  {
    // printf("%d", input);
    input = 0;
    char buf[30]; // large enough
    char *end_ptr;
    wrong_input = 0;

    scanf("%29s", buf); // read everything we have in stdin
    // printf("buffer: %s", buf);
    long int x = strtol(buf, &end_ptr, 0);

    if (*end_ptr != '.')
    {
      input = (int)x;
      // printf("\n%d input:",input);
    }
    else
    {
      wrong_input = 1;
    }

    if (input <= 0 || input > sentence_total)
    {
      printf("%s", text);
      wrong_input = 1;
    }
    clean_stdin();

  } while (wrong_input == 1);
  (input)--;
  return input;
}
//
/// This function is for the double input
///
/// @param sentence_total
///
///
//
void getTwoSentenceNos(int *sentence_total, int *first_sentence_to_switch, int *second_sentence_to_switch)
{

  printf("Nummer des ersten Satzes: ");
  char printone[] = {"Nummer des ersten Satzes: "};
  *first_sentence_to_switch = getInput(printone, *first_sentence_to_switch, *sentence_total);

  printf("Nummer des zweiten Satzes: ");
  do
  {
    char printtwo[] = {"Nummer des zweiten Satzes: "};
    *second_sentence_to_switch = getInput(printtwo, *second_sentence_to_switch, *sentence_total);

  } while (*first_sentence_to_switch == *second_sentence_to_switch);
}

//
/// This function merges calls the function to get the inputs to merge two sentences,
/// creates a temp array than calls the functions according to fill that temp array
/// and swaps the pointer to the temp array with the main array and frees the old array
///
/// @param sentences_seperated_2d the pointer to the array that contains the seperated sentences
///
/// @param temp_sentences_seperated the array that contains the seperated sentences
///
/// @param sentence_total total no of sentences
///
/// @param ptr_sentence_sizes the array that contains the pointer to the sentence sizes
///
/// @param text_size the size of the main text
///
///@return int exit value incase it fails
//
int mergeTwoSentences(char ***sentences_seperated_2d, char **temp_sentences_seperated, int *biggest_sentence, int **sentence_total, int *ptr_sentence_sizes, int text_size)
{
  //get first no
  // =======================================================================
  int first_sentence_to_merge = 0;
  int second_sentence_to_merge = 0;

  getTwoSentenceNos(*sentence_total, &first_sentence_to_merge, &second_sentence_to_merge);
  int size_of_first_sentence = *(ptr_sentence_sizes + first_sentence_to_merge);
  int size_of_second_sentence = *(ptr_sentence_sizes + second_sentence_to_merge);
  int bigger_sentence_size;
  if (size_of_first_sentence > size_of_second_sentence)
  {
    bigger_sentence_size = size_of_first_sentence;
  }
  else
  {
    bigger_sentence_size = size_of_second_sentence;
  }
  int old_sentence_total = **sentence_total;
  --(**sentence_total);

  int new_sentence_size = size_of_first_sentence + size_of_second_sentence + 4; // for .und.

  char **temp_2d;
  temp_2d = get2dArray(**sentence_total, new_sentence_size, text_size);

  if (temp_2d == NULL)
  {
    for (int i = 0; i < old_sentence_total; i++)
    {
      free(temp_2d[i]);
    }
    free(temp_2d);
    return (3);
  }

  if (*biggest_sentence < new_sentence_size)
  {
    *biggest_sentence = new_sentence_size;
  }
  int y2;
  int y;
  for (y = 0, y2 = 0; y < **sentence_total; y++, y2++)
  {
    if (first_sentence_to_merge < second_sentence_to_merge)
    {
      if (y2 == second_sentence_to_merge)
      {
        y2++;
      }
      for (int x = 0; x < *biggest_sentence; x++)
      {
        temp_2d[y][x] = temp_sentences_seperated[y2][x];
      }
    }
    else
    {
      if (y2 == second_sentence_to_merge)
      {
        y2++;
      }
      for (int x = 0; x < *biggest_sentence; x++)
      {
        temp_2d[y][x] = temp_sentences_seperated[y2][x];
      }
    }
  }

  if (first_sentence_to_merge < second_sentence_to_merge)
  {
    concatFirstBigger(first_sentence_to_merge, second_sentence_to_merge, size_of_first_sentence, new_sentence_size, temp_2d, temp_sentences_seperated, ptr_sentence_sizes, **sentence_total);
  }
  else
  {
    concatFirstLower(first_sentence_to_merge, second_sentence_to_merge, size_of_first_sentence, new_sentence_size, temp_2d, temp_sentences_seperated, ptr_sentence_sizes, **sentence_total);
  }

  swap2dArray(&temp_2d, &(*sentences_seperated_2d));

  for (int i = 0; i < old_sentence_total; i++)
  {
    free(temp_2d[i]);
  }
  free(temp_2d);
  return 0;
}
//
/// Prints menu items
///
/// @param void
///
/// @return void
///
//
void printMenu(void)
{
  printf("\nWählen Sie eine Option:\n");
  printf("  t: Text-Statistik\n");
  printf("  s: Zwei Sätze vertauschen\n");
  printf("  c: Zwei Sätze zusammenketten\n");
  printf("  p: Text mit Zeilennummer ausgeben\n");
  printf("  o: Text ohne Zeilennummer ausgeben\n");
  printf("  e: Programm beenden\n\n");
}
//
/// This function saves the first sentence to temp sentence, assigns the second sentence to the first sentence
/// than assigns the temp sentence to the second sentence which results in the sentences swapping
///
/// @param sentences_seperated_2d array containing the sentences
///
/// @param biggest_sentence biggest_sentence
///
/// @param sentence_total sentence_total
///
/// @param ptr_sentence_sizes pointer to the array containing sentence sizes
///
/// @return void
///
void switchTwoSentences(char **sentences_seperated_2d, int biggest_sentence, int *sentence_total, int *ptr_sentence_sizes)
{
  int first_sentence_to_switch = 0;
  int second_sentence_to_switch = 0;

  getTwoSentenceNos(sentence_total, &first_sentence_to_switch, &second_sentence_to_switch);

  char temp_first_sentence[biggest_sentence];

  for (int x = 0; x < biggest_sentence; x++)
  {
    temp_first_sentence[x] = sentences_seperated_2d[first_sentence_to_switch][x];
    sentences_seperated_2d[first_sentence_to_switch][x] = sentences_seperated_2d[second_sentence_to_switch][x];
    sentences_seperated_2d[second_sentence_to_switch][x] = temp_first_sentence[x];
  }

  // need to switch the sizes too
  // the size of first_sentence_to_switch second_sentence_to_switch in sentence_sizes need to switch
  int first_size_temp = ptr_sentence_sizes[first_sentence_to_switch];
  ptr_sentence_sizes[first_sentence_to_switch] = ptr_sentence_sizes[second_sentence_to_switch];
  ptr_sentence_sizes[second_sentence_to_switch] = first_size_temp;
}

//
/// frees rremaining and prints the ending of the programm
///
/// @param sentences_seperated_2d array to be freed
/// @param sentence_total sentence total to free the previous array
/// @param text array to be freed
///
/// @return void
///
//
void exitProgramm(char **sentences_seperated_2d, int *sentence_total, char text[])
{
  free(text);
  for (int i = 0; i < *sentence_total; i++)
  {
    free(sentences_seperated_2d[i]);
  }
  free(sentences_seperated_2d);
}
int ProgrammLoop(char text[], int text_size, int *sentence_total, char **sentences_seperated_2d, int *ptr_sentence_sizes, int biggest_sentence)
{

  int sentence_letters_total = 0;
  int sentence_symbols_total = 0;
  int sentence_lower_total = 0;
  int sentence_upper_total = 0;
  char user_input;
  char check;
  int wrong_input = 0;
  char **temp_sep;
  int exit = 0;
  printMenu();

  do
  {
    if (exit == 3)
    {
      return 3;
    }

    wrong_input = 0;
    while (wrong_input == 0)
    {
      printf("Ihre Wahl: ");
      user_input = getchar();
      if (user_input != '\n')
      {
        check = getchar();
        if (check == '\n')
        {
          wrong_input = 1;
        }
        else
        {
          while (getchar() != '\n')
            ;
          wrong_input = 0;
        }
      }
      else
      {
        wrong_input = 0;
      }
    }

    switch (user_input)
    {
    case 't':
      getTextStatistik(text, text_size, sentence_total, sentence_letters_total, sentence_symbols_total, sentence_lower_total, sentence_upper_total);
      printMenu();

      break;
    case 's':
      if (*sentence_total == 1)
      {
        printf("Nur noch ein Satz vorhanden!\n");
      }
      else
      {
        switchTwoSentences(sentences_seperated_2d, biggest_sentence, sentence_total, ptr_sentence_sizes);
      }
      printMenu();

      break;
    case 'c':
      if (*sentence_total == 1)
      {
        printf("Nur noch ein Satz vorhanden!\n");
      }
      else
      {
        temp_sep = sentences_seperated_2d;
        exit = mergeTwoSentences(&sentences_seperated_2d, temp_sep, &biggest_sentence, &sentence_total, ptr_sentence_sizes, text_size);
        sentence_letters_total += 3;
        sentence_lower_total += 3;
        sentence_symbols_total += 2;
      }
      printMenu();

      break;
    case 'p':
      getSentencesWithNumber(sentence_total, sentences_seperated_2d);
      printMenu();

      break;
    case 'o':
      getText(sentence_total, sentences_seperated_2d);
      printMenu();

      /* code */
      break;
    }
  } while (user_input != 'e');
  printf("Programmende!\n");
  exitProgramm(sentences_seperated_2d, sentence_total, text);

  return 0;
}
