#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h> 
#include <stdio.h>
#include <sys/wait.h>
#include "../libft/libft.h"

             
extern char **environ;

//debug
void    printmatrix(char **tab);
void printlist(t_list *env);
//
void    ft_shellmain(char **cmd, t_list *env);
t_list *env_to_list(char **env);
char **list_to_env(t_list *env);

// bultins
void    ft_env(t_list *env);
int ft_setenv(char **cmd, t_list *env);

//utils
void	ft_lstdelone_if(t_list **list, void *data, int data_size, int (*cmp)());
int     ft_lstsize(t_list *begin);
int		ft_strisalnum(char *str);

#endif