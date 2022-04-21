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

TEST(swe_tests, normal_test) {
    text txt = create_text();
    load(txt, filename);
    testing::internal::CaptureStdout();
    showwordendings(txt);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "s \ns \n\n\na \n\ne \nf \n\nf f f w g \n");
}

TEST(z_tests, normal_test) {
    text txt = create_text();
    load(txt, filename);
    m(txt, 0, 4);
    z(txt);
    string str = txt->begin->contents;
    EXPECT_EQ(str, "sugomA\n");
}

TEST(dd_tests, normal_test) {
    text txt = create_text();
    load(txt, filename);
    m(txt, 0, 4);
    dd(txt);
    string str = txt->begin->next->contents;
    EXPECT_EQ(str, "Amogus\n");
}

#endif
