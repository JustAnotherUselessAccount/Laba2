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

// INPUTDIR

std::string filename = std::string(INPUTDIR) + std::string("/test.txt");
std::string filename2 = std::string(INPUTDIR) + std::string("/test2.txt");
std::string filename3 = std::string(INPUTDIR) + std::string("/test3.txt");

TEST(save_tests, empty_file) {
    text txt = create_text();
    testing::internal::CaptureStdout();
    save(txt, filename2.c_str());
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "There are already no any lines in the text!\n");
}

TEST(save_tests, wrong_filename) {
    text txt = create_text();
    load(txt, filename.c_str());
    testing::internal::CaptureStdout();
    save(txt, "/run/mem");
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "The file /run/mem cannot be opened\n");
}

TEST(save_tests, normal_save) {
    text txt = create_text();
    load(txt, filename.c_str());
    save(txt, "./app/input/test_test.txt");
    load(txt, "./app/input/test_test.txt");
    string str = txt->begin->contents;
    EXPECT_EQ(str, "Amogus\n");
    str = txt->end->contents;
    EXPECT_EQ(str, "fff fff fff rgw seg sg");
}

TEST(move_tests, incorrect_index1) {
    text txt = create_text();
    load(txt, filename.c_str());
    testing::internal::CaptureStdout();
    m(txt, -1, 0);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Incorrect index\n");
}

TEST(move_tests, incorrect_index2) {
    text txt = create_text();
    load(txt, filename.c_str());
    testing::internal::CaptureStdout();
    m(txt, 10, 0);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Incorrect index\n");
}

TEST(move_tests, incorrect_position1) {
    text txt = create_text();
    load(txt, filename.c_str());
    testing::internal::CaptureStdout();
    m(txt, 0, -1);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Incorrect position\n");
}

TEST(move_tests, incorrect_position2) {
    text txt = create_text();
    load(txt, filename.c_str());
    testing::internal::CaptureStdout();
    m(txt, 0, 7);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Incorrect position\n");
}

TEST(move_tests, normal_test) {
    text txt = create_text();
    load(txt, filename.c_str());
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
    load(txt, filename3.c_str());
    testing::internal::CaptureStdout();
    showwordendings(txt);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "\n\n");
}

TEST(swe_tests, normal_test) {
    text txt = create_text();
    load(txt, filename.c_str());
    testing::internal::CaptureStdout();
    showwordendings(txt);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "s \ns \n\n\na \n\ne \nf \n\nf f f w g \n");
}
// ???????? ???? ???????????? ???????? ???? ??????????, ?????????????????? ???????????????? ???? ????, ???????????????? ???? ???????? ???????????? ?????? ??????, ???????????????????????? ???????????????? load

TEST(z_tests, even_symbols_test) {
    text txt = create_text();
    load(txt, filename.c_str());
    m(txt, 0, 4);
    z(txt);
    string str = txt->begin->contents;
    EXPECT_EQ(str, "sugomA\n");
}

TEST(z_tests, odd_symbols_test) {
    text txt = create_text();
    load(txt, filename.c_str());
    m(txt, 6, 1);
    z(txt);
    string str = txt->begin->next->next->next->next->next->next->contents;
    EXPECT_EQ(str, "egefe\n");
}

TEST(z_tests, emply_string_test) {
    text txt = create_text();
    load(txt, filename.c_str());
    m(txt, 2, 0);
    z(txt);
    string str = txt->begin->next->next->contents;
    EXPECT_EQ(str, "\n");
}

TEST(dd_tests, start_test) {
    text txt = create_text();
    load(txt, filename.c_str());
    m(txt, 0, 4);
    dd(txt);
    string str = txt->begin->next->contents;
    EXPECT_EQ(str, "Amogus\n");
}

TEST(dd_tests, end_test) {
    text txt = create_text();
    load(txt, filename.c_str());
    m(txt, 8, 4);
    dd(txt);
    string str = txt->end->contents;
    EXPECT_EQ(str, "fff fff fff rgw seg sg");
}

// ???????????????????? ?????? ?? ?? ???????????????? ???????????????????? - ???? ???????????????? ???????????? ???? ?????????????? ???????????????? ???????????? ??????????????.

#endif
