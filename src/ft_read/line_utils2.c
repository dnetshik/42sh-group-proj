/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmanamel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 09:14:40 by qmanamel          #+#    #+#             */
/*   Updated: 2017/09/25 08:37:03 by qmanamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line.h"

void			scroll_up(t_read *line)
{
	if (line->start.row > 1)
		tputs(tgoto(tgetstr("SF", NULL), 0, line->start.row - 1)
				, 1, &tc_putc);
	line->start.row = 1;
	set_curpos(line);
}

char			*reader(t_read *line)
{
	tputs(tgetstr("ei", NULL), 1, &tc_putc);
	input_loop(line);
	cend(line);
	default_mode();
	ft_putchar('\n');
	if (line->cmd[0] != '!' && !ft_isdigit(line->cmd[1])
			&& ft_strncmp("echo-auto", line->cmd, 9) != 0)
		add_history(line->cmd);
	ft_dlstdelstr(&line->hist);
	free(g_path);
	return (ft_strdup(line->cmd));
}

static	void	paste(t_read *line, char *copy)
{
	char	*join_copy;
	char	*s1;
	char	*s2;

	if (copy)
	{
		s1 = ft_strnew(line->cursor);
		s2 = ft_strnew(ft_strlen(line->cmd) + line->cursor);
		ft_strcpy(s2, line->cmd + line->cursor);
		ft_strncpy(s1, line->cmd, line->cursor);
		ft_free_join(&s1, s1, copy);
		join_copy = ft_strjoin(s1, s2);
		ft_bzero(line->cmd, ft_strlen(line->cmd));
		insert_auto(line, join_copy);
		line->cursor = ft_strlen(s1);
		set_curpos(line);
		free(s1);
		free(s2);
		free(join_copy);
	}
}

int				copy_paste(t_read *line, int key_pressed)
{
	static char		*copy;
	char			*join_copy;

	if (key_pressed == KEY_CTRLD && !ft_strlen(line->cmd))
	{
		ft_bzero(line->cmd, ft_strlen(line->cmd));
		ft_strcpy(line->cmd, "exit");
		return (1);
	}
	if (key_pressed == KEY_CTRLW)
		copy = free_dup(copy, line->cmd + line->cursor);
	if (key_pressed == KEY_CTRLG)
	{
		copy = free_dup(copy, line->cmd + line->cursor);
		join_copy = ft_strnew(line->cursor + 1);
		ft_strncpy(join_copy, line->cmd, line->cursor);
		ft_bzero(line->cmd, ft_strlen(line->cmd));
		insert_auto(line, join_copy);
		free(join_copy);
	}
	if (key_pressed == KEY_CTRLV)
		paste(line, copy);
	return (0);
}

int				echo_auto(t_read *line, char *opt)
{
	int		i;
	char	*tmp2;
	char	*fr;

	i = 0;
	tmp2 = ft_strjoin("echo-auto ", opt);
	fr = tmp2;
	tmp2 = ft_strtrim(tmp2);
	free(fr);
	free(opt);
	if (ft_strcmp(tmp2, "echo-auto") == 0)
	{
		free(tmp2);
		return (0);
	}
	i = open(".auto", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	ft_putstr_fd(line->cmd, i);
	close(i);
	ft_bzero(line->cmd, ft_strlen(line->cmd));
	ft_strcpy(line->cmd, tmp2);
	free(tmp2);
	return (1);
}
