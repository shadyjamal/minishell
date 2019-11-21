/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilslst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 11:03:29 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/11/21 19:20:36 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list *ft_lstdup(t_list **env)
{
    t_list *cur;
    t_list *dup;

    if (!(dup = (t_list *)malloc(sizeof(t_list))))
        return (NULL);
    dup = NULL;
    if (env)
    {
        cur = *env;
        while (cur)
        {
            ft_lstpushback(&dup, cur->content, cur->content_size);
            cur = cur->next;
        }
    }
    return (dup);
}

int ft_lstsize(t_list *begin)
{
    int i;

    i = 0;
    while (begin)
    {
        i++;
        begin = begin->next;
    }
    return (i);
}

t_list *tab_to_list(char **env)
{
    int i;
    int len;
    t_list *head;

    i = 0;
    len = 0;
    head = NULL;
    while (env[i])
    {
        len = ft_strlen(env[i]);
        ft_strreplace(env[i], '=', 0);
        ft_lstpushback(&head, env[i], len + 1);
        i++;
    }
    return (head);
}

char **list_to_tab(t_list *env, int flag)
{
    int len;
    char **tab_env;
    int i;

    len = ft_lstsize(env);
    tab_env = (char **)malloc(sizeof(char *) * (len + 1));
    i = 0;
    while (env)
    {
        if((tab_env[i] = (char *)malloc(sizeof(char) * env->content_size)))
        {
            flag ? ft_strreplace(env->content, 0, '=') : 0;
            ft_memcpy(tab_env[i],
                      env->content,
                      env->content_size);
            flag ? ft_strreplace(env->content, '=', 0) : 0;
            i++;
            env = env->next;
        }
    }
    tab_env[i] = 0;
    return (tab_env);
}

void ft_lstmodifone(t_list *to_mod, char *value)
{
    free(to_mod->content);
    to_mod->content = value;
    to_mod->content_size = ft_strlen(value);
}