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

int    test_access(char *path)
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

char     *ft_cdmoins(t_list **env)
{
    t_list **tofind;
    char *path;

    if ((tofind = ft_lstfind(env, "OLDPWD=", 7)))
    {
        path = (*tofind)->content + 7;
        if (test_access(path))
        {
            chdir(path);
            return (path);
        }
    }
    return (NULL);
}

char     *ft_cdhome(t_list **env)
{
    t_list **tofind;
    char *path;

    if ((tofind = ft_lstfind(env, "HOME=", 5)))
    {
        path = (*tofind)->content + 5;
        if (test_access(path))
        {
            chdir(path);
            return (path);
        }
    }
    return (NULL);
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
    if (ft_strequ(cmd[1], "-"))
        newpath = ft_cdmoins(env);
    else if (cmd[1][0] != '/')
    {
        if (!cmd[1])
            newpath = ft_cdhome(env);
        else
        {
            newpath = ft_strjoin(oldpath, "/"); // leak
            newpath = ft_strjoin(newpath, cmd[1]);
            if (test_access(newpath))
                chdir(newpath);
        }
    }
    else if (test_access(cmd[1]))
    {
        newpath = cmd[1];
        chdir(newpath);
    }
    ft_update_env(env, newpath, oldpath); 
    return (1);
}    