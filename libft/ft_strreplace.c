/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 02:08:30 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/11/19 16:50:50 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strreplace(char *str, char find, char replace)
{
	if (str && (str = ft_strchr(str, find)))
		*str++ = replace;
	return (str);
}