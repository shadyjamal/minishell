/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 11:03:29 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/11/21 11:06:36 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

_Bool		is_dir(char *file_name)
{
	DIR		*dirp;

	if ((dirp = opendir(file_name)))
    {
		closedir(dirp);
        return(1);
    }
    return(0);
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
    tab_env = (char **)ft_memalloc(sizeof(char *) * (len + 1));
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

void ft_lstonedel(t_list **to_del)
{
    t_list *tmp;

    if (to_del && *to_del)
    {
        tmp = *to_del;
        *to_del = tmp->next;
        free(tmp->content);
        free(tmp);
    }
}

void ft_lstmodifone(t_list *to_mod, char *value)
{
    free(to_mod->content);
    to_mod->content = value;
    to_mod->content_size = ft_strlen(value);
}

int ft_strisalnum(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!ft_isalnum(str[i]))
            return (0);
        i++;
    }
    return (1);
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

int ft_is_link(char *path)
{
    struct stat buff;
    return (!lstat(path, &buff) && (buff.st_mode >> 12) == 10);
}