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

static node *create_node(const char *contents);

/**
 * Дублирует текущую строку
 */
void dd(text txt)
{
    /* Проверяем, имеется ли текст */
    if (txt == NULL || txt->length == 0) {
        fprintf(stderr, "There are already no any lines in the text!\n");
        return;
    } 
    
    /* Текст ненулевой длины должен содержать хотя бы одну строку */
    assert(txt->begin != NULL && txt->end != NULL);
    
    /* Находим текущую строку и дублируем*/
    node *current = txt->cursor->line;
    node *pr_next = current->next;
    if (current == txt->end) {
        txt->end->next = create_node(current->contents);
        txt->end->next->previous = txt->end;
        txt->end = txt->end->next;       
    } else {
        current->next = create_node(current->contents);
        current->next->previous = current;
        current->next->next = pr_next;
    }

    txt->cursor->line = current->next;
    txt->length++;
}

static node *create_node(const char *contents)
{  
    assert(contents != NULL);
    
    node *nd;

    if ((nd = (node *) malloc(sizeof(node))) == NULL) {
        fprintf(stderr, "Not enough memory!\n");
        exit(EXIT_FAILURE);
    }
    
    if (strlen(contents) > MAXLINE) {
        fprintf(stderr, "Too long line!\n");
        exit(EXIT_FAILURE);
    }    

    strncpy(nd->contents, contents, MAXLINE);
    nd->contents[MAXLINE] = '\0';    
    nd->previous = NULL;
    nd->next = NULL;   
    
    return nd;
}