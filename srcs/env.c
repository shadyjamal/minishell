/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:17:00 by cjamal            #+#    #+#             */
/*   Updated: 2019/11/15 11:27:25 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_env(t_list *env) // chack commande env
{
    while (env)
    {
        ft_putendl(env->content);
        env = env->next;
    }
}

t_list *env_to_list(char **env)
{
    int i;
    t_list *head;

    i = 0;
    head = NULL;
    while (env[i])
    {
        ft_lstpushback(&head, env[i], ft_strlen(env[i]) + 1);
        i++;
    } 
    return (head);
}

char **list_to_env(t_list *env)
{
    int len;
    char **tab_env;
    int i;

    len = ft_lstsize(env);
    tab_env = (char **)malloc(sizeof(char *) * (len + 1));
    i = 0;
    while (env)
    {
        tab_env[i] = (char*)malloc(sizeof(char) * env->content_size);
        ft_memcpy(tab_env[i], env->content, env->content_size);
        i++;
        env = env->next;
    }
    tab_env[i] = 0;
    return (tab_env);
}

int ft_setenv(char **cmd, t_list *env)
{
    int len;
    char *newenv;

    len = 0;
    if (!ft_strisalnum(cmd[1]))
        return (0); //Error setenv: Variable name must contain alphanumeric characters.
    len = ft_strlen(cmd[1]);
    ft_lstdelone_if(&env, cmd[1], len, &ft_strnequ);
    newenv = ft_strjoin(cmd[1], cmd[2]); // strjoin tableau; newenv = "cmd[1]=cmd[2]""
    ft_lstpushback(&env, newenv, ft_strlen(newenv));
    return (1);
}

// void ft_unsetenv(char **cmd, t_list *env)
// {

// }