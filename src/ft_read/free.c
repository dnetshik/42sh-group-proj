/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmanamel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 13:40:33 by qmanamel          #+#    #+#             */
/*   Updated: 2017/09/25 08:39:12 by qmanamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line.h"

void	free_ptr(char **ptr)
{
	int i;

	if (ptr == NULL)
		return ;
	i = 0;
	while (ptr[i] != NULL)
	{
		free(ptr[i]);
		i++;
	}
	if (ptr != NULL)
		free(ptr);
}

char	*free_dup(char *dest, char *src)
{
	if (dest != NULL)
		free(dest);
	return (ft_strdup(src));
}

void	ft_free_join(char **holder, char *s1, char *s2)
{
	char	*tmp;

	tmp = *holder;
	*holder = ft_strjoin(s1, s2);
	if (tmp != NULL)
		free(tmp);
}
