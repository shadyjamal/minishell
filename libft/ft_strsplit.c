/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 09:08:50 by cjamal            #+#    #+#             */
/*   Updated: 2019/04/02 14:20:18 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_countwords(char const *s, char c)
{
	int cpt;

	cpt = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			while (*s && *s++ != c)
				;
			cpt++;
		}
	}
	return (cpt + 1);
}

static void	ft_extractword(char **tabsplit, char const *s, char c, int *i)
{
	int		last;
	char	*tab;

	last = *i;
	while (*(s + *i) && *(s + *i) != c)
	{
		while (*(s + last) && *(s + last) != c)
			last++;
		*tabsplit = ft_strnew(last - *i + 2);
		tab = *tabsplit;
		while (*(s + *i) && *(s + *i) != c)
		{
			*tab++ = *((char*)s + *i);
			*i += 1;
		}
		*tab = '\0';
	}
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tabsplit;
	int		words;
	int		i;
	int		k;

	if (!s)
		return (NULL);
	words = ft_countwords(s, c);
	if (!(tabsplit = malloc(sizeof(char*) * words + 1)))
		return (NULL);
	k = 0;
	i = 0;
	while (++k < words)
	{
		while (*(s + i) == c)
			i++;
		ft_extractword(tabsplit, s, c, &i);
		tabsplit++;
	}
	*tabsplit = 0;
	return (tabsplit - words + 1);
}
