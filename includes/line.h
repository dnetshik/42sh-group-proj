/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmanamel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 11:14:10 by qmanamel          #+#    #+#             */
/*   Updated: 2017/09/11 11:14:12 by qmanamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_H
# define LINE_H

# include <sys/stat.h>
# include "../libft/libft.h"
# include <signal.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/uio.h>
# include <unistd.h>
# include <dirent.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <sys/ioctl.h>
# define MAX_KEY_LEN 4
# define KEY_CODE_UP "\x1b\x5b\x41\0"
# define KEY_CODE_DO "\x1b\x5b\x42\0"
# define KEY_CODE_RI "\x1b\x5b\x43\0"
# define KEY_CODE_LE "\x1b\x5b\x44\0"
# define KEY_CODE_DEL "\x1b\x5b\x33\x7e"
# define KEY_CODE_HOME "\x1b\x5b\x48\0"
# define KEY_CODE_END "\x1b\x5b\x46\0"
# define KEY_CODE_SUP "\x1b\x1b\x5b\x41"
# define KEY_CODE_SDO "\x1b\x1b\x5b\x42"
# define KEY_CODE_SRI "\x1b\x1b\x5b\x43"
# define KEY_CODE_SLE "\x1b\x1b\x5b\x44"
# define KEY_CTRLL 12
# define HISTORY_PATH ".LINE_HST"
# define MAX_CMD_LEN 4096

typedef struct		s_winsz
{
	size_t			row;
	size_t			col;
}					t_winsz;
typedef struct		s_read
{
	t_dlist			*hist;
	size_t			cursor;
	size_t			length;
	size_t			hist_depth;
	size_t			hist_size;
	t_winsz			winsz;
	t_winsz			start;
	char			cmd[MAX_CMD_LEN];
}					t_read;
struct				s_keymove
{
	int				key;
	void			(*p)(t_read *line);
};
struct				s_keyhist
{
	int				key;
	void			(*p)(t_read *line, t_dlist **hist);
};
struct				s_keymatch
{
	char			*key_code;
	int				key_ret;
};

int					ft_key(void);
char				*ft_read(void);
int					ft_windowsize(t_winsz *winsz);

#endif
