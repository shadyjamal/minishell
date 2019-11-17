/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:13:19 by cjamal            #+#    #+#             */
/*   Updated: 2019/11/17 16:58:30 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// PARSE
// if \t\t\t\t\t\n\n\n\n ls => ls
// if \t\t ls \t\t -a\t\t -l\n\n => ls -a -l
// 

void dispatcher(char **cmd, t_list **env)
{
    if (!cmd[0])
         return ;
    else if (ft_strequ(cmd[0], "cd"))
         ft_cd(cmd, env);
    else if (ft_strequ(cmd[0], "echo"))
         ft_echo(cmd);
    else if (ft_strequ(cmd[0], "env"))
         ft_env(env);
    else if (ft_strequ(cmd[0], "setenv"))
         ft_setenv(cmd, env);
    else if (ft_strequ(cmd[0], "unsetenv"))
         ft_unsetenv(cmd, env);
    // else if (ft_strequ(cmd[0], "exit"))
    //     ft_exit();
    else
        ft_shellmain(cmd, *env);
}

int main(int ac, char *av[], char *environ[])
{
    char *buffer;
    char **cmd;
    t_list *env;

    (void)ac;
    (void)**av;
    env = env_to_list(environ);
    while (1)
    {
        write(1, "\033[95mសួស្តី​ពិភពលោក\033[0m$>", 53);
        if (get_next_line(0, &buffer) > 0)
        {
            cmd = ft_strparse(buffer, ' ');
            dispatcher(cmd, &env);
        }
    }
    return (0);
}