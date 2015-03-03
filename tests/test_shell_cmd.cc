/* Copyright (C) 2015 the ownShell authors and contributors
 * <see AUTHORS file>
 *
 * This module is part of ownShell and is released under
 * the MIT License: http://www.opensource.org/licenses/mit-license.php
*/

#include "gtest/gtest.h"
#include "shell.h"
#include "shell_cmd_test.h"

class ShellCmdTest : public ::testing::Test {
    protected:
        ShellEnv* env;
        MyShellCmd* my_cmd;
        virtual void SetUp(void) {
            this->env = new ShellEnv("my env");
            this->my_cmd = new MyShellCmd(env, "my command", "my command description");
            this->my_cmd->reset();
        }
        virtual void TearDown(void) {
            delete this->my_cmd;
            delete this->env;
        }
};


TEST_F(ShellCmdTest, run) {

    EXPECT_EQ(0, my_cmd->was_called);
    EXPECT_EQ(0, my_cmd->arg_nb);
    char *args[] = {"first", "second"};
    my_cmd->run(args, 2);
    EXPECT_EQ(1, my_cmd->was_called);
    EXPECT_EQ(2, my_cmd->arg_nb);
}
