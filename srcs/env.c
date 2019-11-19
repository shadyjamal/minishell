/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:17:00 by cjamal            #+#    #+#             */
/*   Updated: 2019/11/19 17:58:31 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_display_env(t_list *env)
{
    while (env)
    {
        ft_strreplace(env->content, 0, '=');
        ft_putendl(env->content);
        ft_strreplace(env->content, '=', 0);
        env = env->next;
    }   
}

void    ft_env(t_list **env, char **cmd)
{
    t_list *dup;
    int i;

    if (!cmd[1] && env)
    {
        ft_display_env(*env);
        return ;
    }
    if ((dup = ft_lstdup(env)))
    {
        i = 0;
        while (cmd[++i])
        {
            if (ft_strchr(cmd[i], '='))
                ft_lstpushback(&dup, cmd[i], ft_strlen(cmd[i]) + 1);
            else
                ft_shellmain(cmd + i, dup);
            printlist(dup);
        }
    }
}

// int ft_setenv(char **cmd, t_list **env)
// {
//     int len;
//     char *newenv;
//     t_list **to_modify;

//     len = 0;
//     if (cmd[3])
//         return (0); //Error setenv: Too many arguments.
//     if (!ft_strisalnum(cmd[1]))
//         return (0); //Error setenv: Variable name must contain alphanumeric characters.
//      //leak
//     if ((to_modify = ft_lstfind(env, cmd[1], ft_strlen(cmd[1]))))
//         //ft_lstmodifone(to_modify, ft_strjoin(cmd[1], cmd[2])); // strmultijoin(cmd[1],"=",cmd[2])
//     else
//     {
//         //newenv = ft_strjoin(cmd[1], cmd[2]); // multi join cmd[1], = , cmd[2]
//         ft_lstpushback(env, newenv, ft_strlen(newenv) + 1);
//     }
//     free(newenv);
//     return (1);
// }

int ft_unsetenv(char **cmd, t_list **env)
{
    int i;
    t_list **to_del;

    i = 1;
    while (cmd[i])
    {
        if ((to_del = ft_lstfind(env, cmd[i], ft_strlen(cmd[i]))))
            ft_lstonedel(to_del);
        i++;
    }
    if (i == 1)
        return (0); //unsetenv: Too few arguments.
    return (1);
}