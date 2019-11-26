/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:13:19 by cjamal            #+#    #+#             */
/*   Updated: 2019/11/26 17:37:43 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	kill_procces(int signal)
{
	(void)signal;
	if (g_childprc_pid == 0)
	{
		ft_putchar('\n');
		ft_display_prompt();
	}
}

void	init_var(t_list **env, t_env_var *var)
{
	var->home = *ft_lstfind(env, "HOME", 5);
	var->pwd = *ft_lstfind(env, "PWD", 4);
	var->oldpwd = *ft_lstfind(env, "OLDPWD", 7);
	var->path = *ft_lstfind(env, "PATH", 5);
}

void	dispatcher(char **cmd, t_list **env, t_env_var *var)
{
	if (!cmd[0])
		return ;
	else if (ft_strequ(cmd[0], "exit"))
	{
		freetab(cmd);
		ft_lstdel(env, &freecontent);
		exit(0);
	}
	else if (ft_strequ(cmd[0], "cd"))
		ft_cd(cmd, var);
	else if (ft_strequ(cmd[0], "echo"))
		ft_echo(cmd);
	else if (ft_strequ(cmd[0], "env"))
		ft_env(env, cmd);
	else if (ft_strequ(cmd[0], "setenv"))
		ft_setenv(cmd, env, var);
	else if (ft_strequ(cmd[0], "unsetenv"))
		ft_unsetenv(cmd, env);
	else
		ft_shellmain(cmd, *env);
}

int		ft_tabsize(char **tab)
{
	int size;

	size = 0;
	if (tab)
		while (tab[size])
			size++;
	return (size);
}

int		main(int ac, char *av[], char *environ[])
{
	char		*buffer;
	char		**cmd;
	t_list		*env;
	t_list		*lstcmd;
	t_env_var	var;

	(void)ac;
	(void)**av;
	env = tab_to_list(environ);
	init_var(&env, &var);
	signal(SIGINT, kill_procces);
	while (1)
	{
		ft_display_prompt();
		if (get_next_line(0, &buffer) > 0)
		{
			lstcmd = ft_parsecmd(buffer, &env, &var);
			cmd = list_to_tab(lstcmd, 0);
			ft_lstdel(&lstcmd, &freecontent);
			dispatcher(cmd, &env, &var);
		}
		freeall(buffer, cmd);
		g_childprc_pid = 0;
	}
	return (0);
}
