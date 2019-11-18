/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 20:18:43 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/11/14 20:38:48 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

get_env_pwd(t_list *env)
{
    char *path;

    while(!(path = ft_strnstr(env->content, "PWD", 4)))
    {
        env = env->next;
    }
    return(path);
}

void ft_cd(char **cmd, t_list *env)
{
    const char *path = get_env_pwd(env);
    if(path)
        chdir(ft_strjoin(path,cmd[1]));
    else
        chdir(getcwd(NULL,0));
}