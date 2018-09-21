/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmanamel <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 16:08:23 by qmanamel          #+#    #+#             */
/*   Updated: 2017/06/02 12:07:36 by qmanamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *haystack, int c)
{
	int len;
	int i;

	len = ft_strlen(haystack) + 1;
	i = len - 1;
	while (i >= 0)
	{
		if (haystack[i] == c)
			return ((char *)(haystack + i));
		i--;
	}
	return (NULL);
}
