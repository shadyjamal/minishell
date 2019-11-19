/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 20:28:25 by cjamal            #+#    #+#             */
/*   Updated: 2019/11/19 18:05:01 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdio.h>

// void parse_path(char *full_path, char *path)
// {
// 	char *tmp;
//     char *tmp2;
// 	int diff;
// 	while (*path)
// 	{
// 		if ((tmp2 = ft_strchr(path, '/')) || (tmp2 = ft_strchr(path, '\0')))
// 		{
// 			if ((diff =  (tmp2 - path)) == 2 && ft_strnequ(path, "..", 2))
// 			{
// 				if (*full_path && (tmp = ft_strrchr(full_path, '/')))
// 				{
//                     path += 2 + !!*tmp2;
// 					*tmp = 0;
// 				}
// 			}
// 			else
// 			{
// 				full_path = ft_strcat(full_path,"/");
// 				full_path = ft_strncat(full_path, path, diff);
// 				path += diff + !!*tmp2;
// 			}	
// 		}
//         printf("%s -----------------------> %s\n",full_path,path);
// 	}
// }

// int main()
// {
//     char path[] = "../../Desktop/../minishell/libft/.../../../../../..";
//     char fullpath[] = "/Users/cjamal/Desktop/minishell\0../../Desktop/minishell/libft/../../../link   ";
//     parse_path(fullpath,path);
//     ft_putendl(fullpath);
// }

char	*ft_strnjoin(char	**strings, int n)
{
	char	*concat;
	size_t	size;
	int		i;
	int lenghts[n];

	size = 0;
	i = -1;
	while(++i < n)
	{
		if(!lenghts[i])
			return(NULL);
		lenghts[i] = ft_strlen(strings[i]);
		size += lenghts[i];
	}
	if ((concat = ft_strnew(size)))
	{
		i = -1;
		size = 0;
		while(++i < n)
		{
			ft_strcat(concat + size, strings[i]);
			size += lenghts[i];
		}
	}
	return (concat);
}

int main()
{
	char *s1="hedama";
	 char *s2 = "";
	char *s3="telephone";
	printf("%s",ft_strnjoin((char *[]){s1,s2,s3}, 3));

}