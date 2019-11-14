#include "minishell.h"

void    printmatrix(char **tab)
{
    int i = -1;
    while (tab[++i])
        printf("%s\n", tab[i]);
}