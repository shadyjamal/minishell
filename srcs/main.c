/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:13:19 by cjamal            #+#    #+#             */
/*   Updated: 2019/11/20 19:26:42 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
  
void kill_procces(int signal)
{
	(void)signal;
	if (child_prc_pid == 0)
		write(1, "\n\033[95mសួស្តី​ពិភពលោក\033[0m$>", 54);
	else
		write(1, "\n", 1);
}

void init_var(t_list **env, t_env_var *var)
{
	var->home = *ft_lstfind(env, "HOME", 5);
	var->pwd = *ft_lstfind(env, "PWD", 4);
	var->oldpwd = *ft_lstfind(env, "OLDPWD", 7);
	var->path = *ft_lstfind(env, "PATH", 5);
}

void dispatcher(char **cmd, t_list **env, t_env_var *var)
{
	if (!cmd[0])
		return ;
	else if (ft_strequ(cmd[0], "cd"))
		ft_cd(cmd, var);
	else if (ft_strequ(cmd[0], "echo"))
		ft_echo(cmd);
	else if (ft_strequ(cmd[0], "env"))
		ft_env(env, cmd);
	else if (ft_strequ(cmd[0], "setenv"))
		ft_setenv(cmd, env);
	else if (ft_strequ(cmd[0], "unsetenv"))
		ft_unsetenv(cmd, env);
	// else if (ft_strequ(cmd[0], "exit"))
	//     ft_exit();
	else
		ft_shellmain(cmd, *env);
}

int main(int ac, char *av[], char *environ[])
{
	char *buffer;
	char **cmd;
	t_list *env;
	t_list *lstcmd;
	t_env_var var;

	(void)ac;
	(void)**av;
	env = tab_to_list(environ);
	init_var(&env, &var);
	signal(SIGINT, kill_procces);
	while (1)
	{
		write(1, "\033[95mសួស្តី​ពិភពលោក\033[0m$>", 53);
		if (get_next_line(0, &buffer) > 0)
		{
			lstcmd = ft_parsecmd(buffer);
			//printlist(lstcmd);
			ft_parse_dollar(&lstcmd, &env);
			ft_parse_tilde(&lstcmd, &var);
			//printlist(lstcmd);
			cmd = list_to_tab(lstcmd, 0);
			//printmatrix(cmd);
			dispatcher(cmd, &env, &var);
		}
		child_prc_pid = 0;
	}
	return (0);
}