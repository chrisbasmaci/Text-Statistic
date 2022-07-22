//-----------------------------------------------------------------------------
// a2.c
//
// This programm gets a text from stdin parses the text into individual
// sentences and executes operations on these sentences via user input.
//
//
//
// Author: 11929652
//-----------------------------------------------------------------------------
//

#include <stdlib.h>
#include <stdio.h>
#include "a2.h"
#define MAX_STARTING_CHAR_INPUT 100

int main(void)
{
    char *text;
    int text_size = MAX_STARTING_CHAR_INPUT;
    int sentence_total_old = 0;
    int exit = 0;

    printf("Bitte Text eingeben:\n");

    text = readTextInput(&text_size);

    sentence_total_old = getSentenceTotal(text, text_size);
    int *sentence_total = &sentence_total_old;

    int sentence_sizes[*sentence_total];
    int *ptr_sentence_sizes = sentence_sizes;

    initArrayNull(*sentence_total, ptr_sentence_sizes);

    exit = countSentenceChars(ptr_sentence_sizes, text, text_size);
    if (exit == 1)
    {
        free(text);
        return 1;
    }
    int biggest_sentence = getBiggestSentence(sentence_sizes, sentence_total);

    // Make a 2d array
    char **sentences_seperated_2d;

    sentences_seperated_2d = get2dArray(*sentence_total, biggest_sentence, text_size);
    if (sentences_seperated_2d == NULL)
    {
        exitProgramm(sentences_seperated_2d, sentence_total, text);
        return (3);
    }

    char *sentence_ptrs[*sentence_total];
    getSentencePointers(&(*sentence_ptrs), text, text_size, sentence_total);
    if (*sentence_ptrs == NULL)
    {
        exitProgramm(sentences_seperated_2d, sentence_total, text);
        return (2);
    }

    //set 2d sentences
    fill2dArray(sentence_total, sentence_ptrs, sentence_sizes, sentences_seperated_2d);

    exit = ProgrammLoop(text, text_size, sentence_total, sentences_seperated_2d, ptr_sentence_sizes, biggest_sentence);

    if (exit == 3)
    {
        return 3;
    }

    return 0;
}
