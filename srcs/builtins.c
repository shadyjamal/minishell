/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 18:42:23 by cjamal            #+#    #+#             */
/*   Updated: 2019/11/26 17:46:57 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_echo(char **cmd)
{
	int i;

	i = 0;
	while (cmd[++i])
	{
		ft_putstr(cmd[i]);
		cmd[i] ? write(1, " ", 1) : 0;
	}
	write(1, "\n", 1);
}

void ft_get_cwd(char *ret, char *path)
{
	char *tmp;
	char *tmp2;
	int diff;

	while (*path)
	{
		if ((tmp = ft_strchr(path, '/')) ||
			(tmp = ft_strchr(path, '\0')))
		{
			if ((diff = (tmp - path)) == 2 && ft_strnequ(path, "..", 2))
			{
				if (*ret && (tmp2 = ft_strrchr(ret, '/')))
					*tmp2 = 0;
			}
			else if (diff)
			{
				if ((tmp2 = ft_strrchr(ret, 0)) && (!*ret || tmp2[-1] != '/'))
					ft_strcat(tmp2, "/");
				ft_strncat(tmp2 + 1, path, diff);
			}
			path += diff + !!*tmp;
		}
	}
	!*ret ? ft_strcat(ret, "/") : 0;
}

void ft_update_env(char *pwd, t_env_var *var)
{
	if (var->oldpwd->content)
	{
		ft_lstmodifone(var->oldpwd, ft_strjoin("OLDPWD=", var->pwd->content + 4));
		ft_strreplace(var->oldpwd->content, '=', 0);
	}
	ft_lstmodifone(var->pwd, ft_strjoin("PWD=", pwd));
	ft_strreplace(var->pwd->content, '=', 0);
	free(pwd);
}

char *ft_cdnorm(char **cmd, t_env_var *v, int *err)
{
	if (ft_strequ(cmd[1], "-"))
	{
		if (!v->oldpwd->content)
		{
			*err = 8;
			return (NULL);
		}
		else
			return (ft_strjoin(" ", v->oldpwd->content + 7));
	}
	else if (!is_dir(cmd[1]))
	{
		*err = 6;
		return (NULL);
	}
	else if (*cmd[1] != '/')
		return (ft_strnjoin((char *[]){" ", v->pwd->content + 4, "/", cmd[1]}, 4));
	else
		return (ft_strjoin(" ", cmd[1]));
}

void ft_cd(char **cmd, t_env_var *v)
{
	char *st;
	int err;

	err = 0;
	if (cmd[1] && cmd[2])
		return (ft_print_error(cmd[0], ERR_MNARGS, 0));
	else if (!cmd[1])
		if (!v->home->content)
			return (ft_print_error("HOME", ERR_NOTSET, 0));
		else
			st = ft_strjoin(" ", v->home->content + 5);
	else if (!(st = ft_cdnorm(cmd, v, &err)))
		return (ft_print_error(cmd[0], err, 0));
	if (st && !access(st + 1, F_OK))
	{
		*st = 0;
		ft_get_cwd(st, st + 2);
		if (!chdir(st))
			return (ft_update_env(st, v));
		free(st);
		return (ft_print_error(cmd[0], ERR_PRMDND, 0));
	}
	free(st);
	return (ft_print_error(cmd[0], ERR_NTFOUND, 0));
}

void ft_unsetenv(char **cmd, t_list **env, t_env_var *var)
{
	int i;
	t_list **del;

	i = 1;
	while (cmd[i])
	{
		if ((del = ft_lstfind(env, cmd[i], ft_strlen(cmd[i]) + 1)))
			ft_lstonedel(del);
		i++;
	}
	if (i == 1)
		return (ft_print_error(cmd[0], ERR_FWARGS, 0));
}
