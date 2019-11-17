#include "minishell.h"

void    ft_echo(char **cmd)
{
    int i;

    i = 0;
    while (cmd[++i])
    {
        ft_putstr(cmd[i]);
        write(1, " ",1);
    }
    write(1, "\n",1);
}

int    cd_access(char *path)
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
void    ft_update_env(t_list **env, char *pwd, char *oldpwd)
{
    t_list **tofind;

    if ((tofind = ft_lstfind(env, "OLDPWD=", 7)))
        ft_lstmodifone(tofind, ft_strjoin("OLDPWD=", oldpwd));
    if ((tofind = ft_lstfind(env, "PWD=", 4)))
        ft_lstmodifone(tofind, ft_strjoin("PWD=", pwd));
}

void     ft_cdenv(t_list **env, char *pwd)
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

int    ft_cd(char **cmd, t_list **env)
{
    char *oldpath;
    char *newpath;

    oldpath = NULL;
    newpath = NULL;
    if (cmd[1] && cmd[2])
        return (0); //Error cd: Too many arguments. print_error(path, ERRARGS)
    oldpath = getcwd(NULL, 0);
    if (!cmd[1])
        ft_cdenv(env, "HOME=");
    else if (ft_strequ(cmd[1], "-"))
        ft_cdenv(env, "OLDPWD=");
    else if (cmd[1][0] != '/')
    {
        newpath = ft_strjoin(oldpath, "/"); // leak
        newpath = ft_strjoin(newpath, cmd[1]);
        if (cd_access(newpath))
            chdir(newpath);
    }
    else if (cd_access(cmd[1]))
        chdir(cmd[1]);
    ft_update_env(env, getcwd(NULL, 0), oldpath);
    //free(oldpath);
    //free(newpath);
    return (1);
}    