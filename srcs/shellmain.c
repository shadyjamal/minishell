/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellmain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:16:30 by cjamal            #+#    #+#             */
/*   Updated: 2019/11/15 16:06:30 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *find(char *cmd, char **env)
{
    char *path;
    int i = 0;
    char **paths = ft_strsplit(env[6] + 5, ':');
    while (paths[i])
    {
        if (!access(path = ft_strjoin(paths[i], cmd), F_OK)) // strjoin tableau;
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
    pid_t parrent;
    char *cmd_path;
    char **tab_env;

    tab_env = list_to_env(env);
    //printlist(env);
    //printf("\n\nTAB_ENV*******************\n\n");
    //printmatrix(tab_env);
    if ((cmd_path = find(cmd[0], tab_env)))
    {
        // ft_putendl(cmd_path);
        parrent = fork();
        if (parrent > 0)
            wait(NULL);
        if (parrent == 0)
            execve(cmd_path, cmd, tab_env);
    }
}