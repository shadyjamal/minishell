/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellmain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:16:30 by cjamal            #+#    #+#             */
/*   Updated: 2019/11/17 15:30:55 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int  cmd_access(char *cmd)
{
    if (!access(cmd, F_OK))
    {
        if (!access(cmd, X_OK))
            return (1);
        else
            return (-1); //ft_putendl("permission denied");
    }
    return (0); //ft_putendl("Command not found.");
}

char *find(char *cmd, t_list **env)
{
    char *path;
    int i;
    int ret;
    int permdeny;
    char **paths;
    t_list **getpath;

    i = 0;
    paths = NULL;
    permdeny = 0;
    if ((getpath = ft_lstfind(env, "PATH=", 5)))
    {
        paths = ft_strsplit((*getpath)->content + 5, ':');
        while (paths[i])
        {
            path = ft_strjoin(paths[i], cmd); // Strjoin (paths[i] / cmd)
            if ((ret = cmd_access(path)))
            {
                free(paths); // free(paths[i])
                return (path);
            }
            if (ret < 0)
                permdeny = 1;
            free(path);
            i++;
        }
    }
    free(paths); //fee(paths[i])
    permdeny ? ft_putendl("permission denied") : ft_putendl("Command not found.");
    return (NULL);
}

void ft_shellmain(char **cmd, t_list *env)
{
    pid_t parrent;
    char *cmd_path;
    char **tab_env;
    int ret;

    cmd_path = NULL;
    if ((ret = cmd_access(cmd[0])) > 0) // check permission denied 
        cmd_path = cmd[0];
    else if (ret == -1)
        ft_putendl("Permission denied"); // cmd[0] : Permission denied.
    else
        cmd_path = find(cmd[0], &env);
    if (cmd_path)
    {
        // ft_putendl(cmd_path);
        tab_env = list_to_env(env);
        parrent = fork();
        if (parrent < 0)
            return ; // Fork error exit(Failure)
        if (parrent > 0)
            wait(NULL);
        if (parrent == 0)
            execve(cmd_path, cmd, tab_env);
    }
}