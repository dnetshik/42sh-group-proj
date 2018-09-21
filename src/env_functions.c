/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmanamel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/30 12:59:06 by qmanamel          #+#    #+#             */
/*   Updated: 2017/09/24 12:54:29 by qmanamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void			ft_print_intro(void)
{
	int			fd;
	char		*line;
	int			j;

	j = 1;
	line = NULL;
	fd = open(".Mk_Display", O_RDONLY);
	while (j == 1)
	{
		j = get_next_line(fd, &line);
		ft_putendl(line);
	}
}

char			**local_init(void)
{
	char **tmp;

	tmp = (char **)malloc(sizeof(char *) * 2);
	tmp[0] = ft_strdup("initialized");
	tmp[1] = NULL;
	return (tmp);
}

void			new_env(void)
{
	int			len;
	int			i;
	extern char	**environ;

	tcgetattr(STDIN_FILENO, &g_tattr);
	ft_putstr(CLEAR);
	g_local = local_init();
	ft_print_intro();
	g_shell = (t_shell *)malloc(sizeof(t_shell));
	len = -1;
	i = -1;
	while (environ[++len])
		len++;
	g_shell->g_env = (char **)malloc(sizeof(char *) * (len + 1));
	while (environ[++i])
		g_shell->g_env[i] = ft_strdup(environ[i]);
	g_shell->g_env[i] = NULL;
	g_shell->ret_val = 0;
	g_shell->g_local_i = 0;
	g_shell->g_local_j = 0;
}

char			*ft_getenv(char *s_envstr)
{
	int			i;
	char		*temp;
	char		*ret;

	i = -1;
	while (g_shell->g_env[++i])
	{
		temp = ft_strjoin(s_envstr + 1, "=");
		if (ft_strstartswith(g_shell->g_env[i], temp))
		{
			free(temp);
			ret = ft_strdup(ft_strchr(g_shell->g_env[i], '=') + 1);
			return (ret);
		}
		free(temp);
	}
	return (NULL);
}

int				exec_command_env(void)
{
	int			i;

	i = -1;
	while (g_shell->g_env[++i])
		ft_putendl(g_shell->g_env[i]);
	return (1);
}
