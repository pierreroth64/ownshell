/* Copyright (C) 2015 the ownShell authors and contributors
 * <see AUTHORS file>
 *
 * This module is part of ownShell and is released under
 * the MIT License: http://www.opensource.org/licenses/mit-license.php
*/

#include "gtest/gtest.h"
#include "shell.h"
#include "shell_cmd_test.h"

#define MAX_MODULES 10

class ShellAppTest : public ::testing::Test {
    protected:
        ShellEnv* env = new ShellEnv("my env");
        ShellModule * root = new ShellModule(env, "root", "my root module description");
        ShellApp* app = new ShellApp(env, "myapp>", root);

        virtual void SetUp(void) {

            /*   Commands tree:
             *
             *   root .......................................
             *     |_ "mod 1"
             *     |_ "mod 2"                        level 1
             *     |_ "mod 3" ...............................
             *          |_ "command 1"               level 2
             *          |_ "mod 2" ..........................
             *               |_ "command 2"          level 3
             *               |_ "mod 4" .....................
             *                    |_ "command 1"
             *                    |_ "command 3"     level 4
             *                    |_ "command 4" ............
             */
            /* level 1 */
            this->root->add(new ShellModule(env, "mod 1", "root/mod 1/ description"));
            this->root->add(new ShellModule(env, "mod 2", "root/mod 2/ description"));
            ShellModule* mod_3 = new ShellModule(env, "mod 3", "root/mod 3/ description");
            this->root->add(mod_3);

            /* level 2 */
            mod_3->add(new ShellCmd(env, "command 1", "root/mod 3/command 1 help"));
            ShellModule* mod_2 = new ShellModule(env, "mod 2", "root/mod 3/mod 2/ description");
            mod_3->add(mod_2);

            /* level 3 */
            mod_2->add(new ShellCmd(env, "command 2", "root/mod3/mod 2/command 2 help"));
            ShellModule* mod_4 = new ShellModule(env, "mod 4", "root/mod 3/mod 2/mod 4 description");
            mod_2->add(mod_4);

            /* level 4 */
            mod_4->add(new ShellCmd(env, "command 1", "root/mod 3/mod 2/mod 4/command 1 help"));
            mod_4->add(new ShellCmd(env, "command 3", "root/mod 3/mod 2/mod 4/command 3 help"));
            mod_4->add(new ShellCmd(env, "command 4", "root/mod 3/mod 2/mod 4/command 4 help"));

        }
        virtual void TearDown(void) {
        }
};


TEST_F(ShellAppTest, run) {

    ShellComponent* component;
    vector<string> args;
    vector<string> tokens;

    app->findComponentAndArgsFromTokens(tokens, &component, &args);
    EXPECT_EQ("help", component->getHelp());
}
