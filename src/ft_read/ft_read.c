/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmanamel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 10:23:06 by qmanamel          #+#    #+#             */
/*   Updated: 2017/09/25 08:35:49 by qmanamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line.h"

void	get_cursor_start_pos(t_read *line)
{
	char	answer[100];
	int		i;

	ft_putstr_fd("\e[6n", 0);
	ft_bzero(answer, 100);
	i = read(0, answer, 100);
	answer[i] = 0;
	i = 2;
	line->start.row = ft_atoi(answer + i);
	while (ft_isdigit(answer[i]))
		i++;
	line->start.col = ft_atoi(answer + i + 1);
}

void	match_hist(int key_pressed, t_read *line)
{
	int						i;
	static struct s_keyhist	keyhist[2] = {
		{KEY_UP, &old_hist_entry},
		{KEY_DOWN, &new_hist_entry}
	};

	i = 0;
	while (i < 2)
		if (key_pressed == keyhist[i++].key)
			keyhist[i - 1].p(line, &(line->hist));
}

void	match_move(int key_pressed, t_read *line)
{
	int						i;
	static struct s_keymove	keymove[8] = {
		{KEY_RIGHT, &cright},
		{KEY_LEFT, &cleft},
		{KEY_HOME, &chome},
		{KEY_END, &cend},
		{KEY_SRIGHT, &goto_next_word},
		{KEY_SLEFT, &goto_prev_word},
		{KEY_SPREVIOUS, &goto_prev_line},
		{KEY_SNEXT, &goto_next_line}
	};

	i = 0;
	while (i < 8)
		if (key_pressed == keymove[i++].key)
			keymove[i - 1].p(line);
	match_hist(key_pressed, line);
}

void	input_loop(t_read *line)
{
	int		key_pressed;

	while (1)
	{
		key_pressed = ft_key();
		ft_windowsize(&line->winsz);
		if (line->start.row + line->cursor / line->winsz.col > line->winsz.row)
			line->start.row--;
		match_move(key_pressed, line);
		if (key_pressed > 31 && key_pressed < 127)
			ft_insert_char(line, key_pressed);
		if (key_pressed == KEY_DC || key_pressed == 127)
			ft_delete_char(line, key_pressed);
		if (key_pressed == KEY_CTRLL)
			scroll_up(line);
		if (key_pressed == KEY_CTRLC)
		{
			ft_bzero(line->cmd, ft_strlen(line->cmd));
			break ;
		}
		if (read_u(line, key_pressed))
			break ;
	}
}

char	*ft_read(void)
{
	t_read		line;
	char		cline[MAX_CMD_LEN];
	int			i;
	int			fd;

	raw_mode();
	ft_bzero(&line, sizeof(line));
	line.hist = get_history();
	line.hist_size = ft_dlstsize(line.hist);
	get_cursor_start_pos(&line);
	fd = open(".auto", O_RDONLY);
	i = read(fd, cline, MAX_CMD_LEN);
	cline[i] = '\0';
	i = close(fd) ? 0 : 0;
	ft_strcpy(line.cmd, cline);
	tputs(tgetstr("im", NULL), 1, &tc_putc);
	while (cline[i])
	{
		line.length++;
		line.cursor++;
		ft_putchar_fd(cline[i++], 0);
	}
	return (glob_replace(reader(&line)));
}
