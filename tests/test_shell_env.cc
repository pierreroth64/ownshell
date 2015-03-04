/* Copyright (C) 2015 the ownShell authors and contributors
 * <see AUTHORS file>
 *
 * This module is part of ownShell and is released under
 * the MIT License: http://www.opensource.org/licenses/mit-license.php
*/

#include "gtest/gtest.h"
#include "ownshell.h"

using namespace ownshell;

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

TEST_F(ShellEnvTest, removeEntry) {

    int data = 13;
    env->addEntry("my_data", (void *) &data);

    EXPECT_EQ(13, *((int *) env->getEntry("my_data")));
    env->removeEntry("my_data");
    ASSERT_THROW(env->getEntry("my_data"), shell_except_not_found);
}

TEST_F(ShellEnvTest, getEntriesNumber) {

    int first_data = 13;
    env->addEntry("my_first_data", (void *) &first_data);
    EXPECT_EQ(1, env->getEntriesNumber());

    int second_data = 14;
    env->addEntry("my_second_data", (void *) &second_data);
    EXPECT_EQ(2, env->getEntriesNumber());

    env->removeEntry("my_first_data");
    EXPECT_EQ(1, env->getEntriesNumber());
}

