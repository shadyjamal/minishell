/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:13:19 by cjamal            #+#    #+#             */
/*   Updated: 2019/11/14 19:27:34 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void dispatcher(char **cmd, t_list *env)
{
    if (ft_strequ(cmd[0], "cd"))
        ft_cd(char **cmd, t_list *env);
    else if (ft_strequ(cmd[0], "echo"))
        ft_echo(char **cmd, t_list *env);
    else if (ft_strequ(cmd[0], "echo"))
        ft_env(char **cmd, t_list *env);
    else if (ft_strequ(cmd[0], "echo"))
        ft_setenv(char **cmd, t_list *env);
    else if (ft_strequ(cmd[0], "echo"))
        ft_unsetenv(char **cmd, t_list *env);
    else if (ft_strequ(cmd[0], "exit"))
        ft_exit();
    else
        ft_shellmain(char **cmd, t_list *env);
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
        if (get_next_line(0, &buffer) >= 0)
        {
            cmd = ft_strsplit(buffer, ' ');
            dispatcher(cmd, env);
        }
    }
    return (0);
}