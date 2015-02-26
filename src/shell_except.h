 /* Copyright (C) 2015 Legrand
   All rights reserved

   Shell Library */

/* Exceptions definitions */

#ifndef _SHELL_LIB_I_EXCEPT_H
#define _SHELL_LIB_I_EXCEPT_H

#include <stdexcept>

/**
  shell_except is the base class for all Shell library exceptions
*/
class shell_except: public std::runtime_error
{
    public:
        shell_except(const char *w): std::runtime_error(w) {}
};

class shell_except_not_found: public shell_except
{
    public:
        shell_except_not_found(const char *w): shell_except(w) {}
};

class shell_except_already: public shell_except
{
    public:
        shell_except_already(const char *w): shell_except(w) {}
};
#endif
