/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmanamel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 10:22:01 by qmanamel          #+#    #+#             */
/*   Updated: 2017/09/07 10:22:04 by qmanamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line.h"

void	insert_auto(t_read *line, char *entry)
{
	chome(line);
	tputs(tgetstr("cd", NULL), 0, &tc_putc);
	ft_bzero(line->cmd, MAX_CMD_LEN);
	ft_strcpy(line->cmd, entry);
	line->cursor = ft_strlen(entry);
	line->length = line->cursor;
	tputs(tgetstr("im", NULL), 1, &tc_putc);
	ft_putstr_fd(line->cmd, 0);
	tputs(tgetstr("ei", NULL), 1, &tc_putc);
}

void	ft_insert_char(t_read *line, int key)
{
	if (line->length + 1 >= MAX_CMD_LEN)
		return ;
	ft_memmove(line->cmd + line->cursor + 1, line->cmd + line->cursor,
			MAX_CMD_LEN - line->cursor - 1);
	line->cmd[line->cursor] = key;
	line->length++;
	line->cursor++;
	tputs(tgetstr("im", NULL), 1, &tc_putc);
	ft_putchar_fd(key, 0);
	tputs(tgetstr("ei", NULL), 1, &tc_putc);
}

void	ft_delete_char(t_read *line, int key)
{
	if (key == 127 && !line->cursor)
		return ;
	if (key == 127)
		cleft(line);
	if (line->cursor == line->length)
		return ;
	ft_memmove(line->cmd + line->cursor, line->cmd + line->cursor + 1,
			MAX_CMD_LEN - line->cursor - 1);
	line->length--;
	tputs(tgetstr("cd", NULL), 0, &tc_putc);
	ft_putstr_fd(line->cmd + line->cursor, 0);
	set_curpos(line);
}
