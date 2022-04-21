/**
 * z.c -- функция разворота текущей строки
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

static void reverse(int index, char *contents, int cursor, void *data);

/**
 * Разворачивает строку
 */
void z(text txt)
{
    /* Применяем функцию reverse к каждой строке текста */
    process_forward(txt, reverse, NULL);
}

/**
 * Разворачивает строку
 */
static void reverse(int index, char *contents, int cursor, void *data)
{
    UNUSED(index);
    UNUSED(data);
    
    /* Функция обработчик всегда получает существующую строку */
    assert(contents != NULL);

    /* Разворачиваем строку */    
    if (cursor > -1) {
        int len = strlen(contents);
        if (contents[len-1] == '\n') --len;
        for (int i = 0; i < len/2; i++) {
            char k = contents[i];
            contents[i] = contents[len - 1 - i];
            contents[len - 1 - i] = k;
        }
    }
}