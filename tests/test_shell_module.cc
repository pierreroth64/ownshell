/* Copyright (C) 2015 Legrand
   All rights reserved

   Shell Library - unit test for shell modules */

#include "gtest/gtest.h"
#include "shell.h"
#include "shell_cmd_test.h"

class ShellModuleTest : public ::testing::Test {
    protected:
        ShellEnv* env;
        ShellModule* my_mod;
        virtual void SetUp(void) {
            this->env = new ShellEnv("my env");
            this->my_mod = new ShellModule(env, "my module");
        }
        virtual void TearDown(void) {
            delete this->my_mod;
            delete this->env;
        }
};


TEST_F(ShellModuleTest, registerCmd) {

    MyShellCmd* my_cmd_1 = new MyShellCmd(this->env, "my command 1", "my command 1 description");
    MyShellCmd* my_cmd_2 = new MyShellCmd(this->env, "my command 2", "my command 2 description");

    my_mod->registerCmd(my_cmd_1);
    my_mod->registerCmd(my_cmd_2);
    EXPECT_EQ(2, my_mod->getRegisteredCmdsNb());

    delete my_cmd_1;
    delete my_cmd_2;
}

TEST_F(ShellModuleTest, findCmdByName) {

    MyShellCmd* my_cmd_1 = new MyShellCmd(this->env, "my command 1", "my command 1 description");
    MyShellCmd* my_cmd_2 = new MyShellCmd(this->env, "my command 2", "my command 2 description");

    my_mod->registerCmd(my_cmd_1);
    my_mod->registerCmd(my_cmd_2);
    my_mod->findCmdByName("my command 1");
    ASSERT_THROW(my_mod->findCmdByName("unknown command"), shell_except_not_found);

    delete my_cmd_1;
    delete my_cmd_2;
}


TEST_F(ShellModuleTest, registerCmdAlready) {

    MyShellCmd* my_cmd_1 = new MyShellCmd(this->env, "my command", "my command description");
    MyShellCmd* my_cmd_2 = new MyShellCmd(this->env, "my command", "same command name");

    my_mod->registerCmd(my_cmd_1);
    ASSERT_THROW(my_mod->registerCmd(my_cmd_2), shell_except_already);

    delete my_cmd_1;
    delete my_cmd_2;
}
