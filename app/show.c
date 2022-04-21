/**
 * show.c -- реализует команду вывода хранимого текста на экран
 *
 * Copyright (c) 2017, Alexander Borodin <aborod@petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include <assert.h>
#include "common.h"
#include "text/text.h"

static void show_line(int index, char *contents, int cursor, void *data);

/**
 * Выводит содержимое указанного файла на экран
 */
void show(text txt)
{
    /* Применяем функцию show_line к каждой строке текста */
    process_forward(txt, show_line, NULL);
    printf("\n");
}

/**
 * Выводит содержимое указанного файла на экран
 */
static void show_line(int index, char *contents, int cursor, void *data)
{
    char *str = contents;

    UNUSED(index);
    UNUSED(data);

    /* Функция обработчик всегда получает существующую строку */
    assert(contents != NULL);
    
    char strwc[MAXLINE + 3];

    if (cursor > -1) {
        for (int i = 0; i < cursor; i++) {
            strwc[i] = str[i];
        }
        strwc[cursor] = '|';
        for (int i = cursor + 1; i < MAXLINE + 2; i++) {
            strwc[i] = str[i-1];
        }
    } else {
        for (int i = 0; i < MAXLINE + 2; i++) {
            strwc[i] = str[i];
        }
    }

    int end_of_str = 0;
    for (int i = 0; i < MAXLINE + 3; i++) {
        if (strwc[i] == '\0') {
            end_of_str = i;
            break;
        }
    }
    if (strwc[end_of_str-1] != '\n') {
        strwc[end_of_str+1] = '\0';
        strwc[end_of_str] = '\n';
    }

    str = strwc;

    /* Выводим строку на экран */
    printf("%s", str);
}
