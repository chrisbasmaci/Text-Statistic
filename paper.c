//-----------------------------------------------------------------------------
// a2.c
//
// IGNORE THIS FILE
//
// Author: 11929652
//-----------------------------------------------------------------------------
//
#include <stdlib.h>
#include <ctype.h>

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