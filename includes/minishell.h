#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h> 
#include <stdio.h>
#include <sys/wait.h>
#include "../libft/libft.h"

typedef struct	s_dictionary
{
	char *key;
	char *value;
}				t_dictionary;


typedef struct s_env_var
{
	t_dictionary	home;
	t_dictionary	pwd;
	t_dictionary	oldpwd;
	t_dictionary	path;
}t_env_var;



//parse
t_list *ft_parsecmd(char *buffer);

//debug
void    printmatrix(char **tab);
void printlist(t_list *env);

//
void    ft_shellmain(char **cmd, t_list *env);
t_list *tab_to_list(char **env);
char **list_to_tab(t_list *env);

// bultins
void    ft_echo(char **cmd);
void    ft_env(t_list **env, char **cmd);
int    ft_cd(char **cmd, t_list **env, t_env_var *env_var);
int ft_setenv(char **cmd, t_list **env);
int ft_unsetenv(char **cmd, t_list **env);

//utils
t_list **ft_lstfind(t_list **lst,const char *needle, size_t size);
void ft_lstonedel(t_list **to_del);
void    ft_lstmodifone(t_list **to_mod, char *value);
int     ft_lstsize(t_list *begin);
int		ft_strisalnum(char *str);
t_list  *ft_lstdup(t_list **env);

#endif