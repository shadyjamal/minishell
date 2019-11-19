/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:13:19 by cjamal            #+#    #+#             */
/*   Updated: 2019/11/19 18:50:17 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//
// PARSE $ ~
//
//

void dispatcher(char **cmd, t_list **env)
{
     if (!cmd[0])
          return;
     // else if (ft_strequ(cmd[0], "cd"))
     //      ft_cd(cmd, env, env_var);
     else if (ft_strequ(cmd[0], "echo"))
          ft_echo(cmd);
     else if (ft_strequ(cmd[0], "env"))
          ft_env(env, cmd);
     else if (ft_strequ(cmd[0], "setenv"))
          ft_setenv(cmd, env);
     else if (ft_strequ(cmd[0], "unsetenv"))
          ft_unsetenv(cmd, env);
     // else if (ft_strequ(cmd[0], "exit"))
     //     ft_exit();
     else
          ft_shellmain(cmd, *env);
}

int ft_parse_dollar(t_list **args, t_list *env)
{
     char *dolr;
     char *tmp;
     int len_var;
     t_list *cur_arg;
     t_list **var_env;

     cur_arg = *args;
     while (cur_arg)
     {
          if ((dolr = ft_strchr(cur_arg->content, '$')) && *(dolr + 1))
          {
               *dolr++ = 0;
               len_var = ft_skip_unitl_char(dolr, " \t") - dolr;
               if ((var_env = ft_lstfind(&env, dolr, len_var)))
               { 
                    tmp = cur_arg->content;
                    cur_arg->content = ft_strjoin(cur_arg->content, (*var_env)->content + len_var + 1);
                    cur_arg->content = ft_strjoin(cur_arg->content, dolr + len_var);
                    cur_arg->content_size = ft_strlen(cur_arg->content) + 1;
               }
               else
                    return (0);
          }
          cur_arg = cur_arg->next;
     }
     return (1);
}


int main(int ac, char *av[], char *environ[])
{
     char *buffer;
     char **cmd;
     t_list *env;
     t_list *lstcmd;
     //t_env_var env_var;

     (void)ac;
     (void)**av;
     env = tab_to_list(environ);
     while (1)
     {
          write(1, "\033[95mសួស្តី​ពិភពលោក\033[0m$>", 53);
          if (get_next_line(0, &buffer) > 0)
          {
               lstcmd = ft_parsecmd(buffer);
               //printlist(lstcmd);
               ft_parse_dollar(&lstcmd, env);
               //printlist(lstcmd);
               cmd = list_to_tab(lstcmd , 0);
               //printmatrix(cmd);
               dispatcher(cmd, &env);
          }
     }
     return (0);
}