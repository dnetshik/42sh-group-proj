/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmanamel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/30 13:00:05 by qmanamel          #+#    #+#             */
/*   Updated: 2017/07/30 13:00:08 by qmanamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char			**realloc_envv(int new_size)
{
	char		**new;
	int			i;

	new = (char **)ft_memalloc(sizeof(char *) * (new_size + 1));
	i = -1;
	while (g_shell->g_env[++i] && i < new_size)
	{
		new[i] = ft_strdup(g_shell->g_env[i]);
		free(g_shell->g_env[i]);
	}
	free(g_shell->g_env);
	return (new);
}

int				find_env_var(char *var)
{
	int			i;
	char		*tmp;

	i = -1;
	while (g_shell->g_env[++i])
	{
		tmp = ft_strjoin(var, "=");
		if (ft_strstartswith(g_shell->g_env[i], tmp))
		{
			free(tmp);
			return (i);
		}
		free(tmp);
	}
	return (i);
}

static void		remove_env_var(int var_pos)
{
	int			i;
	int			var_count;

	free(g_shell->g_env[var_pos]);
	g_shell->g_env[var_pos] = NULL;
	i = var_pos;
	var_count = var_pos + 1;
	while (g_shell->g_env[i + 1])
	{
		g_shell->g_env[i] = ft_strdup(g_shell->g_env[i + 1]);
		free(g_shell->g_env[i + 1]);
		i++;
		var_count++;
	}
	g_shell->g_env = realloc_envv(var_count - 1);
}

int				unsetenv_builtin(char **args)
{
	int			i;
	int			var_pos;

	if (!args[0])
	{
		ft_putendl(ENV_ERROR_1);
		return (1);
	}
	i = -1;
	while (args[++i])
	{
		var_pos = find_env_var(args[i]);
		if (g_shell->g_env[var_pos])
			remove_env_var(var_pos);
	}
	return (1);
}
