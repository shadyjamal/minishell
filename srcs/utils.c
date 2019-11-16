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

void    ft_lstmodifone(t_list **to_mod, char *value)
{
    free((*to_mod)->content);
    (*to_mod)->content = NULL;
    (*to_mod)->content = value;
	(*to_mod)->content_size = ft_strlen(value);
}

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

int     ft_lstsize(t_list *begin)
{
    int i;

    i = 0;
    while (begin)
    {
        i++;
        begin = begin->next;
    }
    return (i);
}