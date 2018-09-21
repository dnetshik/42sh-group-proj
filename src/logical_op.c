/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmanamel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 08:21:31 by qmanamel          #+#    #+#             */
/*   Updated: 2017/10/01 09:02:26 by qmanamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int			logical_op_and(char **cmd_1, char **cmd_2)
{
	int		ret;

	g_shell->ret_val = 0;
	ret = run_cmds(cmd_1);
	if (!g_shell->ret_val)
		ret = run_cmds(cmd_2);
	return (ret);
}

int			logical_op_or(char **cmd_1, char **cmd_2)
{
	int		ret;

	g_shell->ret_val = 0;
	ret = run_cmds(cmd_1);
	if (g_shell->ret_val)
		ret = run_cmds(cmd_2);
	return (ret);
}

int			ft_find_len(char *str)
{
	int		len;
	int		bool_int;

	bool_int = 0;
	len = 0;
	while (str[len] && bool_int == 0)
	{
		if (str[len] == '|' && str[len + 1] == '|')
			bool_int = 1;
		else if (str[len] == '&' && str[len + 1] == '&')
			bool_int = 1;
		else
			len++;
	}
	if (str[len + 2] == '&' || str[len + 2] == '|')
	{
		ft_putstr("42sh: parse error near `");
		ft_putchar(str[len + 2]);
		ft_putstr("`\n");
		return (0);
	}
	return (len);
}

int			log_pars(char *str, char **s_cmd, int len)
{
	*s_cmd = (char *)malloc(sizeof(char) * (ft_strlen(str) - (len + 3)));
	*s_cmd = ft_strdup(str + (len + 2));
	*s_cmd = ft_strtrim(*s_cmd);
	return (1);
}

int			logical_op_parse(char *str)
{
	int		len;
	char	*s_cmd;
	char	*f_cmd;
	char	**cmd_2;
	char	**cmd_1;

	if (!(len = ft_find_len(str)))
		return (1);
	f_cmd = find_str(str, len);
	if (!log_pars(str, &s_cmd, len))
		return (1);
	f_cmd = ft_strncpy(f_cmd, str, len);
	cmd_1 = ft_strsplit(f_cmd, ';');
	cmd_2 = ft_strsplit(s_cmd, ';');
	if (str[len + 1] == '&')
		g_shell->log_ret = logical_op_and(cmd_1, cmd_2);
	else if (str[len + 1] == '|')
		g_shell->log_ret = logical_op_or(cmd_1, cmd_2);
	return (g_shell->log_ret);
}
