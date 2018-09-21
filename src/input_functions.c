/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmanamel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 14:32:48 by qmanamel          #+#    #+#             */
/*   Updated: 2017/08/14 14:32:49 by qmanamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char		*ft_strarr(char **str)
{
	int		i;
	char	*temp;
	char	*ret;

	i = 0;
	ret = ft_strdup(str[0]);
	while (str[++i])
	{
		temp = ft_strdup(str[i]);
		ret = ft_strjoin(ret, temp);
	}
	return (ret);
}

static int	check_builtin(char **command)
{
	int		ret;

	ret = 0;
	if (!ft_strcmp(command[0], "echo-auto"))
		ret = cm_echo(command);
	else if (!ft_strcmp(command[0], "history"))
		ret = read_history();
	else if (!ft_strcmp(command[0], "env"))
		ret = exec_command_env();
	else if (!ft_strcmp(command[0], "export"))
		ret = export(command[1]);
	else if (!ft_strcmp(command[0], "unset"))
		ret = ft_unset(command[1]);
	else if (!ft_strcmp(command[0], "setenv"))
		ret = exec_command_setenv(command);
	else if (!ft_strcmp(command[0], "clear"))
		ft_putstr(CLEAR);
	return (ret);
}

int			exec_command_main(char **command)
{
	command = set_vars(command);
	if (command)
	{
		if (!ft_strcmp(command[0], "exit"))
			return (0);
		else if (check_builtin(command))
			return (1);
		else if (command[0][0] == '!')
		{
			ft_putstr("42sh: no such event ");
			ft_putendl(command[0] + 1);
		}
		else if (local_match(command[0]))
			add_local(command[0]);
		else if (!ft_strcmp(command[0], "echo"))
			exec_command_echo(command);
		else if (!ft_strcmp(command[0], "cd"))
			exec_command_cd(command);
		else if (!ft_strcmp(command[0], "unsetenv"))
			unsetenv_builtin(command + 1);
		else
			exec_command(command);
	}
	return (1);
}

int			run_cmds(char **commands)
{
	int		i;
	int		ret;
	char	**command;

	i = -1;
	ret = 0;
	while (commands[++i])
	{
		if (ft_strstr(commands[i], "&&") || ft_strstr(commands[i], "||"))
			ret = logical_op_parse(commands[i]);
		else if (ft_strstr(commands[i], ">") || ft_strstr(commands[i], "<"))
			ret = red_parse(commands[i]);
		else if (ft_strchr(commands[i], 124) &&
			(!ft_strstr(commands[i], "||") && !ft_strstr(commands[i], "&&")))
			ret = pipe_parse(commands[i]);
		else
		{
			command = ft_strsplit(commands[i], ' ');
			ret = exec_command_main(command);
			ft_freestrarr(command);
		}
	}
	return (ret);
}
