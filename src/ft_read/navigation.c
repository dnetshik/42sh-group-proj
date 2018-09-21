/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmanamel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 10:19:50 by qmanamel          #+#    #+#             */
/*   Updated: 2017/09/07 10:19:52 by qmanamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line.h"

void	goto_next_word(t_read *line)
{
	while (line->cmd[line->cursor] != ' ' && line->cursor != line->length)
		cright(line);
	while (line->cmd[line->cursor] == ' ' && line->cursor != line->length)
		cright(line);
}

void	goto_prev_word(t_read *line)
{
	if (line->cursor && line->cmd[line->cursor - 1] == ' ')
		cleft(line);
	while (line->cmd[line->cursor] == ' ' && line->cursor)
		cleft(line);
	while (line->cmd[line->cursor] != ' ' && line->cursor)
		cleft(line);
	if (line->cursor)
		cright(line);
}

void	goto_next_line(t_read *line)
{
	line->cursor = line->cursor + line->winsz.col > line->length ?
		line->length : line->cursor + line->winsz.col;
	set_curpos(line);
}

void	goto_prev_line(t_read *line)
{
	line->cursor = line->cursor < line->winsz.col ? 0 : line->cursor -
		line->winsz.col;
	set_curpos(line);
}
