#ifndef TEST_H
#define TEST_H

#include <gtest/gtest.h>
#include <string>

#include <fcntl.h>
#include <errno.h>
//#include <unistd.h>

using namespace std;

extern "C" {
    #include "showwordendings.c"
    #include "save.c"
    #include "m.c"
    #include "z.c"
    #include "dd.c"
    #include "text/text.h"
    #include "text/_text.h"
    #include "common.h"
    #include "load.c"
    #include "text/create_text.c"
}

char* filename = "./app/input/test.txt";
char* filename2 = "./app/input/test2.txt";
char* filename3 = "./app/input/test3.txt";

TEST(save_tests, empty_file) {
    text txt = create_text();
    testing::internal::CaptureStdout();
    save(txt, filename2);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "There are already no any lines in the text!\n");
}

TEST(save_tests, wrong_filename) {
    text txt = create_text();
    load(txt, filename);
    testing::internal::CaptureStdout();
    save(txt, "?");
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "The file ? cannot be opened\n");
}

TEST(save_tests, normal_save) {
    text txt = create_text();
    load(txt, filename);
    save(txt, "./app/input/test_test.txt");
    load(txt, "./app/input/test_test.txt");
    string str = txt->begin->contents;
    EXPECT_EQ(str, "Amogus\n");
    str = txt->end->contents;
    EXPECT_EQ(str, "fff fff fff rgw seg sg");
}

TEST(move_tests, incorrect_index1) {
    text txt = create_text();
    load(txt, filename);
    testing::internal::CaptureStdout();
    m(txt, -1, 0);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Incorrect index\n");
}

TEST(move_tests, incorrect_index2) {
    text txt = create_text();
    load(txt, filename);
    testing::internal::CaptureStdout();
    m(txt, 10, 0);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Incorrect index\n");
}

TEST(move_tests, incorrect_position1) {
    text txt = create_text();
    load(txt, filename);
    testing::internal::CaptureStdout();
    m(txt, 0, -1);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Incorrect position\n");
}

TEST(move_tests, incorrect_position2) {
    text txt = create_text();
    load(txt, filename);
    testing::internal::CaptureStdout();
    m(txt, 0, 7);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Incorrect position\n");
}

TEST(move_tests, normal_test) {
    text txt = create_text();
    load(txt, filename);
    m(txt, 1, 4);

    node *current = txt->begin;
    int cur_index = 0;

    while (cur_index != 1) {
        current = current->next;
        cur_index++;
    }

    EXPECT_EQ(txt->cursor->line, current);
    EXPECT_EQ(txt->cursor->position, 4);
}


TEST(swe_tests, only_spaces) {
    text txt = create_text();
    load(txt, filename3);
    testing::internal::CaptureStdout();
    showwordendings(txt);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "\n\n");
}

TEST(swe_tests, normal_test) {
    text txt = create_text();
    load(txt, filename);
    testing::internal::CaptureStdout();
    showwordendings(txt);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "s \ns \n\n\na \n\ne \nf \n\nf f f w g \n");
}
// Тест на пустой файл не нужен, поскольку проверка на то, является ли файл пустым или нет, производится функцией load

TEST(z_tests, even_symbols_test) {
    text txt = create_text();
    load(txt, filename);
    m(txt, 0, 4);
    z(txt);
    string str = txt->begin->contents;
    EXPECT_EQ(str, "sugomA\n");
}

TEST(z_tests, odd_symbols_test) {
    text txt = create_text();
    load(txt, filename);
    m(txt, 6, 1);
    z(txt);
    string str = txt->begin->next->next->next->next->next->next->contents;
    EXPECT_EQ(str, "egefe\n");
}

TEST(z_tests, emply_string_test) {
    text txt = create_text();
    load(txt, filename);
    m(txt, 2, 0);
    z(txt);
    string str = txt->begin->next->next->contents;
    EXPECT_EQ(str, "\n");
}

TEST(dd_tests, start_test) {
    text txt = create_text();
    load(txt, filename);
    m(txt, 0, 4);
    dd(txt);
    string str = txt->begin->next->contents;
    EXPECT_EQ(str, "Amogus\n");
}

TEST(dd_tests, end_test) {
    text txt = create_text();
    load(txt, filename);
    m(txt, 8, 4);
    dd(txt);
    string str = txt->end->contents;
    EXPECT_EQ(str, "fff fff fff rgw seg sg");
}

// Аналогично как и с функцией переворота - за проверку текста на пустоту отвечает другая функция.

#endif
