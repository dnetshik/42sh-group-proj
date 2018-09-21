/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmanamel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/30 12:59:56 by qmanamel          #+#    #+#             */
/*   Updated: 2017/08/16 14:44:42 by qmanamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int			env_overwrite_pos(char *str)
{
	int		i;
	char	*temp;

	i = -1;
	while (g_shell->g_env[++i])
	{
		temp = ft_strjoin(str, "=");
		if (ft_strstartswith(g_shell->g_env[i], temp))
		{
			free(temp);
			return (i);
		}
		free(temp);
	}
	return (i);
}

char		**realloc_env(int new_size)
{
	char	**new;
	int		i;

	new = (char **)ft_memalloc(sizeof(char *) * (new_size));
	i = -1;
	while (g_shell->g_env[++i] && i < new_size)
	{
		new[i] = ft_strdup(g_shell->g_env[i]);
		free(g_shell->g_env[i]);
	}
	free(g_shell->g_env);
	return (new);
}

void		set_env(char *key, char *value)
{
	int		pos;
	char	*temp;

	pos = env_overwrite_pos(key);
	temp = ft_strjoin("=", value);
	if (g_shell->g_env[pos])
	{
		free(g_shell->g_env[pos]);
		if (value)
			g_shell->g_env[pos] = ft_strjoin(key, temp);
		else
			g_shell->g_env[pos] = ft_strjoin(key, "=");
	}
	else
	{
		g_shell->g_env = realloc_env(pos + 2);
		if (value)
			g_shell->g_env[pos] = ft_strjoin(key, temp);
		else
			g_shell->g_env[pos] = ft_strjoin(key, "=");
	}
	free(temp);
}

int			exec_command_setenv(char **s_env_str)
{
	if (s_env_str[3])
	{
		ft_putendl(SETENV_SYNTAX);
		return (1);
	}
	else if (!s_env_str[1] || !s_env_str[2] || !ft_isprint_str(s_env_str[1])
	|| !ft_isprint_str(s_env_str[2]))
	{
		ft_putendl(SETENV_SYNTAX);
		return (1);
	}
	set_env(s_env_str[1], s_env_str[2]);
	return (1);
}
