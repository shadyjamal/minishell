#include "minishell.h"

void	ft_lstdelone_if(t_list **list, void *data, int data_size, int (*cmp)())
{
	t_list	*cur;
	t_list	*tmp;
	
	if (*list && cmp((*list)->content, data, data_size))
	{
		cur = *list;
		*list = (*list)->next;
		free(cur);
        return ;
	}
	cur = *list;
	while (cur && cur->next)
	{
		if (cmp(cur->next->content, data) == 1)
		{
			tmp = cur->next;
			cur->next = tmp->next;
			free(tmp);
            break ;
		}
		cur = cur->next;
	}
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