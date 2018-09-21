/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmanamel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/30 12:59:15 by qmanamel          #+#    #+#             */
/*   Updated: 2017/10/01 08:05:14 by qmanamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void			exit_shell(void)
{
	ft_freestrarr(g_shell->g_env);
	exit(0);
}

int				exec_shell_cmd(char *path, char **args)
{
	pid_t		pid;
	int			status;

	pid = fork();
	signal(SIGINT, &proccess_handler);
	if (pid == 0)
		execve(path, args, g_shell->g_env);
	else if (pid < 0)
	{
		free(path);
		ft_putendl("Fork failed to create new process");
	}
	else
	{
		waitpid(pid, &status, 0);
		g_shell->ret_val = WEXITSTATUS(status);
	}
	if (path)
		free(path);
	return (1);
}

int				is_exec(char *path, struct stat f, char **command)
{
	if (f.st_mode & S_IFREG)
	{
		if (f.st_mode & S_IXUSR)
			return (exec_shell_cmd(path, command));
		else
		{
			ft_putstr("42sh v.2.0: permmision denied: ");
			ft_putendl(path);
		}
		free(path);
		return (1);
	}
	free(path);
	return (0);
}

int				path_check(char **command)
{
	int			i;
	char		*bin_path;
	char		**path;
	struct stat f;

	i = -1;
	path = ft_strsplit(ft_getenv("$PATH"), ':');
	while (path && path[++i])
	{
		bin_path = ft_strjoinfr(ft_strjoin(path[i], "/"), command[0], 0);
		if (lstat(bin_path, &f) == -1)
			free(bin_path);
		else
		{
			ft_freestrarr(path);
			return (is_exec(bin_path, f, command));
		}
	}
	ft_freestrarr(path);
	return (0);
}

int				exec_command(char **cmd)
{
	struct stat	d_stat;

	if (path_check(cmd))
		return (0);
	if (lstat(cmd[0], &d_stat) != -1)
	{
		if (d_stat.st_mode & S_IXUSR)
			return (exec_shell_cmd(ft_strdup(cmd[0]), cmd));
	}
	ft_putstr("42sh v.2.0 : command not found ");
	ft_putendl(cmd[0]);
	return (0);
}
