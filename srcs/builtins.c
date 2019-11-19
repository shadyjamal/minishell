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

// void parse_path(char *full_path, char *path)
// {
// 	char *tmp;
// 	int diff;
// 	while (*path)
// 	{
// 		if ((tmp = ft_strchr(path, '/')) || (tmp = ft_strchr(path, '\0')))
// 		{
// 			if ((diff =  (tmp - path) == 2 && ft_strnequ(*path, "..", 2)))
// 			{
// 				if (*full_path && (tmp = ft_strrchr(full_path, '/')))
// 				{
// 					*tmp = 0;
// 					path += 3;
// 				}
// 			}
// 			else
// 			{
// 				ft_strcat(full_path,"/");
// 				ft_strncat(full_path, path, diff);
// 				path += diff + 1;
// 			}	
// 		}
// 	}
// }

int cd_access(char *path)
{
	if (!access(path, F_OK))
	{
		if (!access(path, X_OK))
			return (1);
		else
		{
			ft_putendl("Permission Denied"); // print_error(path, ERRPERM)
			return (0);
		}
	}
	else
	{
		ft_putendl("no such file or directory"); // print_error(path, ERRNOTFD)
		return (0);
	}
}
void ft_update_env(t_list **env, char *pwd, char *oldpwd)
{
	t_list **tofind;

	if ((tofind = ft_lstfind(env, "OLDPWD=", 7)))
		ft_lstmodifone(tofind, ft_strjoin("OLDPWD=", oldpwd));
	if ((tofind = ft_lstfind(env, "PWD=", 4)))
		ft_lstmodifone(tofind, ft_strjoin("PWD=", pwd));
}

void ft_cdenv(t_list **env, char *pwd)
{
	t_list **tofind;
	int len;

	len = ft_strlen(pwd);
	if ((tofind = ft_lstfind(env, pwd, len)))
	{
		if (cd_access((*tofind)->content + len))
			chdir((*tofind)->content + len);
	}
}

// int ft_cd(char **cmd, t_list **env)
// {
// 	int dir_changed;

// 	dir_changed = 1;
// 	if (cmd[1] && cmd[2])
// 		return (0); //Error cd: Too many arguments. print_error(path, ERRARGS)
// 	if (!cmd[1])
// 		dir_changed = chdir(home);
// 	else if (ft_strequ(cmd[1], "-"))
// 		dir_changed = chdir(oldpwd);
// 	else if (cd_access(cmd[1]))
// 		dir_changed = chdir(cmd[1]);
// 	if (dir_changed == 0 && cmd[1])
// 		if(ft_strequ(cmd[1],"-"))
// 			ft_update_env(env, oldpwd, pwd);
// 		if(is_link(cmd[1]))
// 			ft_update_env(env, ft_pwd(), pwd);
// 		else
// 			ft_update_env(env, getcwd(NULL,0), pwd);
// 	}

// 	return (1);
// }

//OLDPATH env variable makaytmhach wakha dir lih unset env o ila 3awadti creyitih makayb9ach ytmodifa