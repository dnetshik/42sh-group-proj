/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmanamel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 13:36:40 by qmanamel          #+#    #+#             */
/*   Updated: 2017/10/01 08:05:53 by qmanamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char		**ft_strarrdup(char **str)
{
	int		i;
	char	**f_str;

	i = -1;
	while (str[++i])
		i++;
	f_str = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (str[++i])
		f_str[i] = ft_strdup(str[i]);
	f_str[i] = NULL;
	return (f_str);
}

char		**ft_strjoinarr(char **str)
{
	int		i;
	char	*ret;
	char	*temp;
	char	**f_ret;

	f_ret = (char **)malloc(sizeof(char *) * 2);
	i = 0;
	ret = ft_strdup(str[i]);
	while (str[++i])
	{
		temp = ft_strdup(str[i]);
		ret = ft_strjoin(ret, " ");
		ret = ft_strjoin(ret, temp);
	}
	f_ret[0] = ft_strdup(ret);
	f_ret[1] = NULL;
	return (f_ret);
}

void		execve_pipe(char ***cmd)
{
	pid_t	pid;
	char	**main_command;

	while (*cmd != NULL)
	{
		pipe(g_shell->p);
		pid = fork();
		if (pid == 0)
		{
			dup2(g_shell->fd_in, 0);
			if (*(cmd + 1) != NULL)
				dup2(g_shell->p[1], 1);
			close(g_shell->p[0]);
			main_command = ft_strjoinarr(*cmd);
			run_cmds(main_command);
			exit(EXIT_FAILURE);
		}
		else
		{
			close(g_shell->p[1]);
			g_shell->fd_in = g_shell->p[0];
			cmd++;
		}
	}
	waitpid(pid, 0, 0);
}

int			exec_pipe(char **str, int len)
{
	char	***pipes;
	char	**temp_pipe;
	int		i;

	pipes = (char ***)malloc(sizeof(char **) * (len));
	i = -1;
	while (str[++i])
	{
		temp_pipe = ft_strsplit(str[i], ' ');
		pipes[i] = ft_strarrdup(temp_pipe);
	}
	pipes[i] = NULL;
	execve_pipe(pipes);
	ft_freestrarr(temp_pipe);
	return (1);
}

int			pipe_parse(char *command)
{
	char	**temp_pipes;
	int		len;

	len = 0;
	g_shell->fd_in = 0;
	temp_pipes = ft_strsplit(command, '|');
	len = -1;
	while (temp_pipes[++len])
		len++;
	exec_pipe(temp_pipes, len);
	return (1);
}
