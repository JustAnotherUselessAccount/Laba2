/**
 * common.h -- прототипы функций реализации команд редактора
 * 
 * Copyright (c) 2017, Alexander Borodin <aborod@petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#ifndef COMMON_H
#define COMMON_H

#include "text/text.h"

/* Декларирует неиспользуемый аргумент,
 * корректно подавляя предупреждение вида "unused parameter" */
#define UNUSED(x) (void)(x)

/**
 * Выводит содержимое указанного файла на экран
 */
void show(text txt);

/**
 * Выводит символы концов слов
 */
void showwordendings(text txt);

/**
 * Разворачивает текущую строку
 */
void z(text txt);

/**
 * Загружает содержимое указанного файла
 */
void load(text txt, char *filename);

/**
 * Сохраняет текущий текст в файл
 */
void save(text txt, char *filename);

/**
 * Дублирует текущую строку
 */
void dd(text txt);

/**
 * Перемещает курсор
 */
void m(text txt, int index, int position);

#endif
