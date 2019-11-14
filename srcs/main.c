#include "minishell.h"

extern char **environ;

int main(void)
{
    char *buffer;

    //printmatrix(environ);
    while (1)
    {
        write(1,"\033[95mសួស្តី​ពិភពលោក\033[0m$>", 53);
        if (get_next_line(0, &buffer) >= 0)
            ft_shellmain(buffer);
    }
    return (0);
}