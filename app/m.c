/**
 * save.c -- функция загрузки текста из файла
 * 
 * Copyleft (c) 2022, Evgeniy Smirnov
 *
 * This code is licensed under a CC-style license.
 */

#include <stdio.h>
#include <assert.h>
#include "common.h"
#include "text/text.h"
#include "text/_text.h"

/**
 * Перемещает курсор
 */
void m(text txt, int index, int position)
{
    if (index < 0 || index >= txt->length) {
        printf("Incorrect index\n");
        return;
    }

    if (position < 0 || position >= MAXLINE) {
        printf("Incorrect position\n");
        return;
    }

    node *current = txt->begin;
    int cur_index = 0;

    while (cur_index != index) {
        current = current->next;
        cur_index++;
    }

    int end_of_str = 0;
    for (int i = 0; i < MAXLINE + 1; i++) {
        if ((current->contents)[i] == '\0') {
            end_of_str = i;
            break;
        }
    }
    
    if (position >= end_of_str) {
        printf("Incorrect position\n");
        return;
    }

    txt->cursor->line = current;
    txt->cursor->position = position;
}