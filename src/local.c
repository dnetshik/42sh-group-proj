/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmanamel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 11:43:34 by qmanamel          #+#    #+#             */
/*   Updated: 2017/10/01 08:57:30 by qmanamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int			local_match(char *s)
{
	int		i;
	int		m;

	i = 0;
	m = 0;
	while (s[i])
	{
		if (m)
			return (1);
		if (i > 0 && s[i] == '=')
			m = 1;
		i++;
	}
	return (0);
}

char		**set_vars(char **ptr)
{
	int		i;
	char	**tmp;
	char	*t;
	int		j;

	i = 0;
	while (ptr[i])
		i++;
	tmp = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	j = 0;
	while (ptr[++i])
	{
		if (ptr[i][0] == '$' && ptr[i][1] == '?')
			tmp[j++] = ft_itoa(WEXITSTATUS(g_shell->ret_val));
		if (ptr[i][0] == '$')
		{
			t = ft_strdup(ft_match(ptr[i]));
			tmp[j++] = t;
		}
		else
			tmp[j++] = ft_strdup(ptr[i]);
	}
	tmp[j] = NULL;
	return (tmp);
}

static char	*str_before(char *fuck, char c)
{
	char	*ret;
	int		i;

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

static void	add_loc(char *key, char *value)
{
	int		i;
	char	**tmp;

	i = 0;
	while (g_local[i])
		i++;
	tmp = (char **)malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (g_local[++i])
		tmp[i] = ft_strdup(g_local[i]);
	tmp[i++] = ft_strjoin(key, value);
	tmp[i] = NULL;
	g_local = tmp;
}

void		add_local(char *s)
{
	char	*key;
	char	*value;

	key = str_before(s, '=');
	value = ft_strdup(ft_strchr(s, '='));
	add_loc(key, value);
	free(key);
	free(value);
}
