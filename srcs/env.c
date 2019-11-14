/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:17:00 by cjamal            #+#    #+#             */
/*   Updated: 2019/11/14 19:27:30 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_env(char **env)
{
    int i = -1;
    while (env[++i])
        ft_putendl(env[i]);
}

t_list *env_to_list(char **env)
{
    int i;
    t_list *head;

    i = 0;
    head = NULL;
    while(env[i])
    {
        ft_lstpushback(&head,env[i],ft_strlen(env[i]));
        i++;
    } 
}