/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeanderrors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 12:33:55 by cjamal            #+#    #+#             */
/*   Updated: 2019/11/25 12:33:58 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

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

void	freecontent(void *content, size_t contentsize)
{
	ft_bzero(content, contentsize);
	free(content);
}

void    freetab (char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
    tab = NULL;
}
void ft_print_error(char *str, int er, char c)
{
    if (er < 8)
    {
        ft_putstr(str);
        ft_putstr(": ");
    }
    er == ERR_CMDNTFD ? ft_putendl("Command not found.") : 0;
    er == ERR_PRMDND ? ft_putendl("Permission denied.") : 0;
    er == ERR_MNARGS ? ft_putendl("Too many arguments.") : 0;
    er == ERR_FWARGS ? ft_putendl("Too few arguments.") : 0;
    er == ERR_ALFA ? ft_putendl("Variable name must contain alphanum chars.") : 0;
    er == ERR_FSTLTR ? ft_putendl("Variable name must begin with a letter.") : 0;
    er == ERR_NTFOUND ? ft_putendl("No such file or directory.") : 0;
    er == ERR_UNMATCHED ? ft_putstr("Unmatched ") : 0;
    er == ERR_UKNUSR ? ft_putstr("Unknown user: ") : 0;
    er == ERR_NOT_DIR ? ft_putendl("Not a directory") : 0;
    if (er >= 8)
    {
        er == ERR_UNMATCHED ? ft_putchar(c) : 0;
        er == ERR_UKNUSR ? ft_putstr(str) : 0;   
        ft_putendl(".");
    }
}