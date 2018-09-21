/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmanamel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 17:06:11 by qmanamel          #+#    #+#             */
/*   Updated: 2017/10/01 08:32:11 by qmanamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static char		*str_before(char *fuck, char c)
{
	char		*ret;
	int			i;

	i = 0;
	while (fuck[i] && fuck[i] != c)
		i++;
	ret = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (fuck[i] && fuck[i] != c)
	{
		ret[i] = fuck[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

static void		add_to_env(char *value)
{
	char		*key;
	char		*val;

	if (glob_match("*=*", value))
	{
		val = ft_strdup(ft_strchr(value, '=') + 1);
		key = str_before(value, '=');
		set_env(key, val);
		free(key);
		free(val);
	}
}

int				export(char *key)
{
	int			i;
	char		*add;

	if (!key)
		return (1);
	i = 0;
	while (g_local[i])
	{
		if (ft_strncmp(key, g_local[i], ft_strlen(key)) == 0 &&
				g_local[i][ft_strlen(key)] == '=')
		{
			add = g_local[i];
			add_to_env(add);
			break ;
		}
		i++;
	}
	return (1);
}
