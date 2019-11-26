/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 12:34:15 by cjamal            #+#    #+#             */
/*   Updated: 2019/11/26 11:18:23 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strisalnum(char *str)
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

_Bool	is_dir(char *file_name)
{
	DIR		*dirp;

	if ((dirp = opendir(file_name)))
	{
		closedir(dirp);
		return (1);
	}
	return (0);
}

int		ft_is_link(char *path)
{
	struct stat buff;

	return (!lstat(path, &buff) && (buff.st_mode >> 12) == 10);
}

t_list	*isenv(char *str, t_env_var *var)
{
	if (ft_strequ(str, "HOME"))
		return (var->home);
	else if (ft_strequ(str, "PWD"))
		return (var->pwd);
	else if (ft_strequ(str, "OLDPWD"))
		return (var->oldpwd);
	else if (ft_strequ(str, "PATH"))
		return (var->path);
	return (NULL);
}

void	ft_display_prompt(void)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	ft_putstr("-> ");
	ft_putstr(ft_strrchr(pwd, '/'));
	ft_putstr(" $>");
	free(pwd);
}
