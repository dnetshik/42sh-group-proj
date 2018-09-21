/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstgettail.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmanamel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 10:13:19 by qmanamel          #+#    #+#             */
/*   Updated: 2017/09/07 10:13:27 by qmanamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstgettail(t_dlist *dlst)
{
	while (dlst)
	{
		if (dlst->next)
			dlst = dlst->next;
		else
			break ;
	}
	return (dlst);
}
