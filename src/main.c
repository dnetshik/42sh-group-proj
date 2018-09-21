/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmanamel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/30 13:00:24 by qmanamel          #+#    #+#             */
/*   Updated: 2017/07/30 14:12:05 by qmanamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int			ft_parse_check(char *str)
{
	int		i;
	char	**split;

	split = ft_strsplit(str, ';');
	if (!split)
		return (1);
	i = -1;
	while (str[++i])
	{
		if (str[i] == ';' && str[i + 1] == ';')
		{
			ft_putendl("42sh: parse error near ';;'");
			return (1);
		}
	}
	return (0);
}

static char	*ft_start(void)
{
	char	*input;

	display_prompt();
	input = ft_read();
	input = d_quote(input);
	input = s_quote(input);
	input = backslash(input);
	input = ignore(input, '\'');
	return (input);
}

int			main(void)
{
	char	*input;
	int		ret;
	char	**commands;

	new_env();
	while (42)
	{
		input = ft_start();
		tcsetattr(STDIN_FILENO, TCSADRAIN, &g_tattr);
		input = ft_strtrim(input);
		if (ft_isemptystr(input) || ft_parse_check(input)
			|| !ft_strcmp(input, ";"))
		{
			free(input);
			continue ;
		}
		commands = ft_strsplit(input, ';');
		free(input);
		ret = run_cmds(commands);
		ft_freestrarr(commands);
		if (!ret)
			exit_shell();
	}
	ft_freestrarr(g_shell->g_env);
	return (0);
}
