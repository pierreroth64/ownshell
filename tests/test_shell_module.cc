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
            this->my_mod = new ShellModule(env, "my module", "description of my module");
        }
        virtual void TearDown(void) {
            delete this->my_mod;
            delete this->env;
        }
};


TEST_F(ShellModuleTest, add) {

    MyShellCmd* my_cmd_1 = new MyShellCmd(this->env, "my command 1", "my command 1 description");
    MyShellCmd* my_cmd_2 = new MyShellCmd(this->env, "my command 2", "my command 2 description");

    my_mod->add(my_cmd_1);
    my_mod->add(my_cmd_2);
    EXPECT_EQ(2, my_mod->getComponentsNb());

    delete my_cmd_1;
    delete my_cmd_2;
}


TEST_F(ShellModuleTest, addAlready) {

    MyShellCmd* my_cmd_1 = new MyShellCmd(this->env, "my command", "my command description");
    MyShellCmd* my_cmd_2 = new MyShellCmd(this->env, "my command", "same command name");

    my_mod->add(my_cmd_1);
    ASSERT_THROW(my_mod->add(my_cmd_2), shell_except_already);

    delete my_cmd_1;
    delete my_cmd_2;
}

TEST_F(ShellModuleTest, getHelp) {

    ShellModule* mod_1 = new ShellModule(env, "mod1", "mod1 description");
    ShellModule* mod_2 = new ShellModule(env, "mod2", "mod2 description");
    EXPECT_EQ("mod1 description", mod_1->getHelp());
}
