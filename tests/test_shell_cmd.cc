/* Copyright (C) 2015 Legrand
   All rights reserved

   Shell Library - unit test for shell cmds */

#include "gtest/gtest.h"
#include "shell.h"

/* Shell command concrete class for testing */
class MyShellCmd : public ShellCmd {
    public:
        MyShellCmd(ShellEnv* env, std::string name, std::string description):  ShellCmd(env, name, description) {
            this->was_called = 0;
            this->arg_nb = 0;
        } ;
        bool was_called;
        unsigned int arg_nb;
        virtual void run(char** argv, int argc);
        void reset(void);

};

void MyShellCmd::run(char** argv, int argc)
{
    this->was_called = 1;
    this->arg_nb = argc;
}

void MyShellCmd::reset(void)
{
    this->was_called = 0;
    this->arg_nb = 0;
}
/* ----------- */

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
