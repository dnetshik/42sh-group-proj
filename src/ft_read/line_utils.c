/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmanamel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 14:59:41 by qmanamel          #+#    #+#             */
/*   Updated: 2017/09/25 08:38:27 by qmanamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line.h"

int				read_u(t_read *line, int key_pressed)
{
	int		fd;
	char	*s;

	if (copy_paste(line, key_pressed) == 1)
		return (1);
	if (key_pressed == '\t' && ft_strlen(line->cmd))
		return (autocomplete(line));
	if (line->cmd[0] == '!' && key_pressed == '\n')
	{
		s = ft_history(line->cmd);
		feed_line(line, s);
		free(s);
		ft_putstr_fd(line->cmd, 0);
		if (line->cmd[0] == '!')
			return (1);
	}
	else if (key_pressed == '\n')
	{
		fd = open(".auto", O_WRONLY | O_TRUNC | O_CREAT, 0644);
		close(fd);
		return (1);
	}
	return (0);
}

static	int		cmd_start(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	i--;
	if (str[i] == '|' || str[i] == ';' || str[i] == '&')
		return (1);
	return (0);
}

static char		*options(char *line)
{
	char	**tmp;
	char	*ret;
	int		i;
	char	*fr;

	i = 0;
	tmp = ft_strsplit(line, ' ');
	while (tmp[i])
		i++;
	if (i == 1)
		ret = get_bins(tmp[i - 1]);
	else if (cmd_start(tmp[i - 2]))
		ret = get_bins(tmp[i - 1]);
	else
		ret = auto_files(tmp[i - 1]);
	free_ptr(tmp);
	fr = ft_strtrim(ret);
	free(ret);
	return (fr);
}

static char		*replace(char *line, char *option)
{
	int			i;
	int			j;
	char		**tmp;
	char		*ret;

	i = 0;
	j = 0;
	tmp = ft_strsplit(line, ' ');
	while (tmp[j])
		j++;
	j--;
	ret = ft_strdup(" ");
	while (tmp[i])
	{
		if (i != j)
			ft_free_join(&ret, ret, tmp[i]);
		else
			ft_free_join(&ret, ret, option);
		ft_free_join(&ret, ret, " ");
		i++;
	}
	free_ptr(tmp);
	free(option);
	return (ret);
}

int				autocomplete(t_read *line)
{
	char	*tmp2;
	char	**tmp;
	char	*opt;
	int		i;

	opt = options(line->cmd);
	tmp = ft_strsplit(opt, ' ');
	i = 0;
	while (tmp[i])
		i++;
	free_ptr(tmp);
	if (i == 1)
	{
		tmp2 = replace(line->cmd, opt);
		opt = ft_strtrim(tmp2);
		ft_free_join(&tmp2, opt, " ");
		insert_auto(line, tmp2);
		return (0);
	}
	else
		return (echo_auto(line, opt));
	return (0);
}
