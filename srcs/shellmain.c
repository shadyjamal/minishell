#include "minishell.h"

void    ft_shellmain(char *buffer)
{
    char **cmd;
    pid_t   parrent;

    cmd = ft_strsplit(buffer, ' ');
    if (!ft_strcmp(cmd[0], "ls"))
    {
        parrent = fork();
        if (parrent > 0)
            wait(NULL);
        if (parrent == 0)
            execve("/bin/ls", cmd, environ);
    }
    if (!ft_strcmp(buffer,"exit"))
        exit(0);
}