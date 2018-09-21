/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_match.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmanamel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 09:01:01 by qmanamel          #+#    #+#             */
/*   Updated: 2017/10/01 09:01:19 by qmanamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char		*ft_match(char *s)
{
	char	*tmp;
	int		i;

	i = 0;
	while (g_shell->g_env[i] != NULL)
	{
		if (!ft_strncmp(&s[1], &(g_shell->g_env[i][0]), ft_strlen(&s[1]))
				&& (g_shell->g_env[i][ft_strlen(&s[1])] == '='))
		{
			tmp = ft_strchr(g_shell->g_env[i], '=');
			return (&tmp[1]);
		}
		i++;
	}
	i = -1;
	while (g_local[++i] != NULL)
	{
		if (!ft_strncmp(&s[1], &(g_local[i][0]), ft_strlen(&s[1]))
				&& (g_local[i][ft_strlen(&s[1])] == '='))
		{
			tmp = ft_strchr(g_local[i], '=');
			return (&tmp[1]);
		}
	}
	return ("");
}

char		*find_str(char *str, int len)
{
	char	*ret;
	int		i;

	ret = (char *)malloc(sizeof(char) * len);
	i = -1;
	while (++i < len)
		ret[i] = str[i];
	ret[i] = '\0';
	return (ret);
}
