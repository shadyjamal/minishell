#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h> 
#include <stdio.h>
#include <sys/wait.h>
#include "../libft/libft.h"

             
extern char **environ;

//debug
void    printmatrix(char **tab);
//
void    ft_shellmain(char *buffer);
t_list *env_to_list(char **env);


#endif