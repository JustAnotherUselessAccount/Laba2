/**
 * editor.c -- строковый текстовый редактор
 * 
 * Copyright (c) 2017, Alexander Borodin <aborod@petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text/text.h"
#include "common.h"

#define MAXLINE 255

int main()
{
    char cmdline[MAXLINE + 1];
    char *cmd;
    char *arg;
    char *arg2;
    char current_filename[MAXLINE + 1];
    
    /* Создаем объект для представления текста */
    text txt = create_text();

    /* Цикл обработки команд */
    while (1) {
        printf("ed > ");
        
        /* Получаем команду */
        fgets(cmdline, MAXLINE, stdin);

        /* Извлекаем имя команды */
        if ((cmd = strtok(cmdline, " \n")) == NULL) {
            continue;
        }

        /* Распознаем поддерживаемую команду */
        
        /* Завершаем работу редактора */
        if (strcmp(cmd, "quit") == 0) {
            fprintf(stderr, "Bye!\n");
            break;
        }

        /* Загружаем содержимое файла, заданного параметром */
        if (strcmp(cmd, "load") == 0) {
            if ((arg = strtok(NULL, " \n")) == NULL) {
                fprintf(stderr, "Usage: load filename\n");
            } else {
                strcpy(current_filename, arg);
                load(txt, current_filename);
            }
            continue;
        }

        /* Выводим текст */
        if (strcmp(cmd, "show") == 0) {
            show(txt);
            continue;
        }

        /* Сохраняем файл */
        if (strcmp(cmd, "save") == 0) {
            if ((arg = strtok(NULL, " \n")) != NULL) {
                strcpy(current_filename, arg);
            }
            save(txt, current_filename);
            continue;
        }

        /* Перемещаем курсор */
        if (strcmp(cmd, "m") == 0) {
            if ((arg = strtok(NULL, " \n")) == NULL) {
                fprintf(stderr, "Usage: m index position\n");
                continue;
            }
            if ((arg2 = strtok(NULL, " \n")) == NULL) {
                fprintf(stderr, "Usage: m index position\n");
                continue;
            }
            m(txt, atoi(arg), atoi(arg2));
            continue;
        }

        /* Выводим символы концов строк */
        if (strcmp(cmd, "showwordendings") == 0) {
            showwordendings(txt);
            continue;
        }

        /* Переворачиваем текущую строку */
        if (strcmp(cmd, "z") == 0) {
            z(txt);
            continue;
        }

        /* Дублируем текущую строку */
        if (strcmp(cmd, "dd") == 0) {
            dd(txt);
            continue;
        }
        
        /* Если команда не известна */
        fprintf(stderr, "Unknown command: %s\n", cmd);
    }

    return 0;
}
