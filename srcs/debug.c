#include "minishell.h"

void    printmatrix(char **tab)
{
    int i = -1;
    while (tab[++i])
        ft_putendl(tab[i]);
}

void printlist(t_list *env)
{
    while (env)
    {
        printf("%s\n", env->content);
        env = env->next;
    }
}