/* Copyright (C) 2015 Legrand
   All rights reserved

   Shell Library - unit test for shell runner */

#include "gtest/gtest.h"
#include "shell.h"
#include "shell_cmd_test.h"

class ShellRunnerTest : public ::testing::Test {
    protected:
        ShellEnv* env;
        ShellRunner* my_runner;
        virtual void SetUp(void) {
            this->env = new ShellEnv("my env");
            this->my_runner = new ShellRunner(env, "my runner");
        }
        virtual void TearDown(void) {
            delete this->my_runner;
            delete this->env;
        }
};


TEST_F(ShellRunnerTest, registerModule) {

    MyShellCmd* my_cmd_1 = new MyShellCmd(this->env, "my command 1", "my command 1 description");
    MyShellCmd* my_cmd_2 = new MyShellCmd(this->env, "my command 2", "my command 2 description");
    ShellModule * my_mod = new ShellModule(this->env, "my module");

    my_mod->registerCmd(my_cmd_1);
    my_mod->registerCmd(my_cmd_2);

    my_runner->registerModule(my_mod);

    delete my_cmd_1;
    delete my_cmd_2;
    delete my_mod;
}

TEST_F(ShellRunnerTest, findModuleByName) {

    ShellModule* mod_1 = new ShellModule(this->env, "my module 1");
    ShellModule* mod_2 = new ShellModule(this->env, "my module 2");

    my_runner->registerModule(mod_1);
    my_runner->registerModule(mod_2);

    my_runner->findModuleByName("my module 1");
    ASSERT_THROW(my_runner->findModuleByName("unknown module"), shell_except_not_found);

    delete mod_1;
    delete mod_2;
}


TEST_F(ShellRunnerTest, registerModuleAlready) {

    ShellModule* mod_1 = new ShellModule(this->env, "my module");
    ShellModule* mod_2 = new ShellModule(this->env, "my module");

    my_runner->registerModule(mod_1);
    ASSERT_THROW(my_runner->registerModule(mod_2), shell_except_already);

    delete mod_1;
    delete mod_2;
}

TEST_F(ShellRunnerTest, runCmd) {

    MyShellCmd* my_cmd_1 = new MyShellCmd(this->env, "my command 1", "my command 1 description");
    MyShellCmd* my_cmd_2 = new MyShellCmd(this->env, "my command 2", "my command 2 description");
    ShellModule* my_mod_1 = new ShellModule(this->env, "my module 1");

    char *args[] = {"first", "second"};

    my_mod_1->registerCmd(my_cmd_1);
    my_mod_1->registerCmd(my_cmd_2);
    my_runner->registerModule(my_mod_1);

    my_runner->runCmd("my module 1", "my command 1", args, 5);

    EXPECT_EQ(5, my_cmd_1->lastArgNumber());
    EXPECT_EQ(0, my_cmd_2->lastArgNumber());

    delete my_cmd_1;
    delete my_cmd_2;
    delete my_mod_1;
}
