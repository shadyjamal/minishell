#include "minishell.h"

void ft_print_error(char *str, int er, char c)
{
    if (er < 8)
    {
        ft_putstr(str);
        ft_putstr(": ");
    }
    er == ERR_CMDNTFD ? ft_putendl("Command not found.") : 0;
    er == ERR_PRMDND ? ft_putendl("Permission denied.") : 0;
    er == ERR_MNARGS ? ft_putendl("Too many arguments.") : 0;
    er == ERR_FWARGS ? ft_putendl("Too few arguments.") : 0;
    er == ERR_ALFA ? ft_putendl("Variable name must contain alphanum chars.") : 0;
    er == ERR_FSTLTR ? ft_putendl("Variable name must begin with a letter.") : 0;
    er == ERR_NTFOUND ? ft_putendl("No such file or directory.") : 0;
    er == ERR_UNMATCHED ? ft_putstr("Unmatched ") : 0;
    er == ERR_UKNUSR ? ft_putstr("Unknown user: ") : 0;
    er == ERR_NOT_DIR ? ft_putendl("Not a directory") : 0;
    if (er >= 8)
    {
        er == ERR_UNMATCHED ? ft_putchar(c) : 0;
        er == ERR_UKNUSR ? ft_putstr(str) : 0;   
        ft_putendl(".");
    }
}