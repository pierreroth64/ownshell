/* Copyright (C) 2015 Legrand
   All rights reserved

   CCTV Library */

#include "gtest/gtest.h"
#include "shell.h"

class ShellEnvTest : public ::testing::Test {
    protected:
        ShellEnv* env = new ShellEnv("my env");
};

TEST_F(ShellEnvTest, addEntry) {

    int my_data = 12;
    env->addEntry("my_data", (void *) &my_data);
    EXPECT_EQ(12, *((int *) env->getEntry("my_data")));
}

TEST_F(ShellEnvTest, getEntry) {

    int first_data = 13;
    env->addEntry("my_first_data", (void *) &first_data);
    int second_data = 14;
    env->addEntry("my_second_data", (void *) &second_data);

    EXPECT_EQ(14, *((int *) env->getEntry("my_second_data")));
    EXPECT_EQ(13, *((int *) env->getEntry("my_first_data")));
}

TEST_F(ShellEnvTest, getEntryNotFound) {

    int first_data = 13;
    env->addEntry("my_first_data", (void *) &first_data);
    ASSERT_THROW(env->getEntry("my_unknown_data"), shell_except_not_found);
}
