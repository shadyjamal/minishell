/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellmain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:16:30 by cjamal            #+#    #+#             */
/*   Updated: 2019/11/14 19:27:18 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *find(char *cmd)
{
    char *path;
    int i = 0;
    char **paths = ft_strsplit(environ[6] + 5, ':');
    while (paths[i])
    {
        if (!access(path = ft_strjoin(paths[i], cmd), F_OK))
        {
            if (!access(path, X_OK))
                return (path);
            else
            {
                ft_putendl("permission denied");//first permission denied 
                free(path);
                return (NULL);
            }
        }
        free(path);
        i++;
    }
    ft_putendl("file not found");
    return (NULL);
}

void ft_shellmain(char **cmd, t_list *env)
{
    char **cmd;
    pid_t parrent;
    char *cmd_path;

    if ((cmd_path = find(cmd[0])))
    {
        // ft_putendl(cmd_path);
        parrent = fork();
        if (parrent > 0)
            wait(NULL);
        if (parrent == 0)
            execve(cmd_path, cmd, environ);
    }
}