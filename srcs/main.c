/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:13:19 by cjamal            #+#    #+#             */
/*   Updated: 2019/11/18 17:32:21 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//
// PARSE $ ~
//
//

// void dispatcher(char **cmd, t_list **env)
// {
//      if (!cmd[0])
//           return;
//      else if (ft_strequ(cmd[0], "cd"))
//           ft_cd(cmd, env);
//      else if (ft_strequ(cmd[0], "echo"))
//           ft_echo(cmd);
//      else if (ft_strequ(cmd[0], "env"))
//           ft_env(env);
//      else if (ft_strequ(cmd[0], "setenv"))
//           ft_setenv(cmd, env);
//      else if (ft_strequ(cmd[0], "unsetenv"))
//           ft_unsetenv(cmd, env);
//      // else if (ft_strequ(cmd[0], "exit"))
//      //     ft_exit();
//      else
//           ft_shellmain(cmd, *env);
// }

char *ft_parse_quote(t_list **args, char *buffer, char c)
{
     int k;
     int j;
     char buff[200];

     k = 0;
     j = 0;
     while (*buffer)
     {
          if (k == 0 && (*buffer == '\t' || *buffer == ' '))
               break;
          else if (*buffer == c)
               k = (k + 1) % 2;
          else
               buff[j++] = *buffer;
          buffer++;
     }
     buff[j++] = 0;
     if (!k)
          ft_lstpushback(args, buff, j);
     else
     {
          ft_putendl("unmatched c");
          return (NULL);
     }
     return (buffer);
}

t_list *ft_parsecmd(char *buffer)
{
     char c;
     char *tmp;
     int i;
     t_list *args;

     args = NULL;
     while (*buffer)
     {
          buffer = ft_skip_chars(buffer, "\t ");
          tmp = ft_skip_unitl_char(buffer, "\t '\"");
          i = tmp - buffer;
          if ((c = *tmp) == '"' || c == '\'')
          {
               if (!(buffer = ft_parse_quote(&args, buffer, c)))
                    return (NULL);
          }
          else
          {
               buffer[i++] = 0;
               ft_lstpushback(&args, buffer, i);
               buffer += i - !c;
          }
     }
     return (args);
}

int main(int ac, char *av[], char *environ[])
{
     char *buffer;
     char **cmd;
     t_list *env;
     t_list *args;

     (void)ac;
     (void)**av;
     env = env_to_list(environ);
     while (1)
     {
          write(1, "\033[95mសួស្តី​ពិភពលោក\033[0m$>", 53);
          if (get_next_line(0, &buffer) > 0)
          {
               args = ft_parsecmd(buffer);
               printlist(args);
               //cmd = ft_strparse(buffer, ' ');
               //dispatcher(cmd, &env);
          }
     }
     return (0);
}