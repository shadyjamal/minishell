/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:17:00 by cjamal            #+#    #+#             */
/*   Updated: 2019/11/15 18:10:26 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_env(t_list **env) // chack commande env
{
    t_list *cur;
    int i = 0;

    cur = *env;
    ft_putendl("TEST");
    while (cur)
    {
        i++;
        ft_putendl(cur->content);
        cur = cur->next;
    }
    ft_putnbr(i);
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

int ft_setenv(char **cmd, t_list **env)
{
    int len;
    char *needle;
    char *newenv;
    t_list **to_modify;

    len = 0;
    if (cmd[3])
        return (0); //Error setenv: Too many arguments.
    if (!ft_strisalnum(cmd[1]))
        return (0); //Error setenv: Variable name must contain alphanumeric characters.
    needle = ft_strjoin(cmd[1], "=");
    if ((to_modify = ft_lstfind(env, needle, ft_strlen(needle)))) 
        ft_lstmodifone(to_modify, ft_strjoin(needle, cmd[2]));
    else
    {
        newenv = ft_strjoin(needle, cmd[2]);
        ft_lstpushback(env, newenv, ft_strlen(newenv) + 1);
    }
    free(needle);
    return (1);
}

int ft_unsetenv(char **cmd, t_list **env)
{
    int i;
    t_list **to_del;
    char *needle;

    i = 1;
    while (cmd[i])
    {
        needle = ft_strjoin(cmd[i],"=");
        if ((to_del = ft_lstfind(env, needle, ft_strlen(needle))))
            ft_lstonedel(to_del);
        free(needle);
        i++;
    }
    return (1);
}