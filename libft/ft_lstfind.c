#include "libft.h"

t_list **ft_lstfind(t_list **lst,const char *needle, size_t size)
{
    t_list **ptr;

    ptr = lst;
    if (!needle)
        return(NULL);
    while (*ptr)
    {
        if((*ptr)->content_size >= size && !ft_memcmp((*ptr)->content, needle, size))
            return(ptr);
        ptr = &(*ptr)->next;
    }
    return (NULL);
}