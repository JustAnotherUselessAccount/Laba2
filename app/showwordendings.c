/**
 * showwordendings.c -- функция показа символов концов слов
 * 
 * Copyleft (c) 2022, Evgeniy Smirnov
 *
 * This code is licensed under a CC-style license.
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "common.h"
#include "text/text.h"

static void show_endings(int index, char *contents, int cursor, void *data);

/**
 * Выводит символы концов слов
 */
void showwordendings(text txt)
{
    /* Применяем функцию show_endings к каждой строке текста */
    process_forward(txt, show_endings, NULL);
}

/**
 * Выводит символы концов слов
 */
static void show_endings(int index, char *contents, int cursor, void *data)
{
    char *str = contents;

    UNUSED(index);
    UNUSED(data);
    UNUSED(cursor);

    /* Функция обработчик всегда получает существующую строку */
    assert(contents != NULL);

    /* Выводим символы на экран на экран */
    int flag = 0;
    for (int i = 0; i <= strlen(str); i++) {
        if (flag) {
            for (int j = i - 1; j >= 0; j--) {
                if (str[j] >= 'a' && str[j] <= 'z') {
                    printf("%c ", str[j]);
                    flag = 0;
                    break;
                }
            }
            flag = 0;
        } else {
            if (str[i] == ' ' || str[i] == '\n' || str[i] == '\0') {
                flag = 1;
            }
        }
    }
    printf("\n");
}
