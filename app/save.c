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
 * Сохраняет текущий текст в файл
 */
void save(text txt, char *filename)
{
    FILE *f;

    /* Проверяем, имеется ли текст */
    if (txt == NULL || txt->length == 0) {
        printf("There are already no any lines in the text!\n");
        return;
    } 
    
    /* Текст ненулевой длины должен содержать хотя бы одну строку */
    assert(txt->begin != NULL && txt->end != NULL);

    /* Открываем файл для записи, контролируя ошибки */
    if ((f = fopen(filename, "w")) == NULL) {
        printf("The file %s cannot be opened\n", filename);
        return;
    }

    /* Стартуем с начальной строки текста */
    node *current = txt->begin;

    /* Сохраняем содержимое строка за строкой */
    while (current) {
        fputs(current->contents, f);
        current = current->next;
    }

    fclose(f);
}