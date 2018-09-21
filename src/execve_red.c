/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_red.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmanamel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 08:50:24 by qmanamel          #+#    #+#             */
/*   Updated: 2017/10/01 08:13:31 by qmanamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static int	ft_check_red(int i)
{
	int		fd;

	fd = 0;
	if (g_shell->red->opt == FILE_OUT)
		fd = creat(g_shell->red->f_files[i], 0644);
	else if (g_shell->red->opt == FILE_APPEND)
		fd = open(g_shell->red->f_files[i], O_RDWR | O_APPEND);
	else if (g_shell->red->opt == FILE_IN)
		fd = open(g_shell->red->f_files[i], O_RDWR);
	return (fd);
}

void		execve_red(void)
{
	pid_t	pid;
	int		fd;
	int		i;

	i = -1;
	while (g_shell->red->f_files[++i])
	{
		pid = fork();
		fd = ft_check_red(i);
		if (pid == -1)
			ft_putendl("Error in Forking");
		else if (pid == 0)
		{
			if (g_shell->red->opt == FILE_IN)
				dup2(fd, 0);
			else
				dup2(fd, 1);
			close(fd);
			run_cmds(g_shell->red->command);
			exit(EXIT_SUCCESS);
		}
	}
	waitpid(pid, 0, 0);
}

int			prepare_red(char *str, char **files, char **command)
{
	int		i;
	int		ret;

	i = ft_check_file(str, &ret);
	if (str[i] == '>')
		*files = ft_strdup(str + (i + 2));
	else
		*files = ft_strdup(str + (i + 1));
	*command = (char *)malloc(sizeof(char) * (i - 1));
	*command = ft_strncpy(*command, str, (i - 2));
	return (ret);
}

char		*get_red_command(char *str, char **files, int *opt)
{
	char	*command;

	*opt = prepare_red(str, &(*files), &command);
	return (command);
}

int			red_parse(char *str)
{
	char	*command;

	g_shell->red = (t_red *)malloc(sizeof(t_red));
	g_shell->red->opt = 0;
	command = get_red_command(str, &g_shell->red->files, &g_shell->red->opt);
	g_shell->red->f_files = ft_strsplit(g_shell->red->files, ' ');
	g_shell->red->command = ft_strsplit(command, ';');
	execve_red();
	return (1);
}
