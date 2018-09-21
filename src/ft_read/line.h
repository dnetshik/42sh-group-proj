/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmanamel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 08:44:02 by qmanamel          #+#    #+#             */
/*   Updated: 2017/09/25 09:16:30 by qmanamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_H
# define LINE_H

# include <sys/stat.h>
# include "libft/libft.h"
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
# define KEY_CTRLC 3
# define KEY_CTRLD 4
# define KEY_CTRLW 23
# define KEY_CTRLG 7
# define KEY_CTRLV 22
# define MAX_CMD_LEN 4096

char				*g_path;

char				**set_local(char **vars);

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
void				ft_dlstdelstr(t_dlist **lst);
void				goto_next_word(t_read *line);
void				goto_prev_word(t_read *line);
void				goto_next_line(t_read *line);
void				goto_prev_line(t_read *line);
void				set_curpos(t_read *line);
void				cleft(t_read *line);
void				cright(t_read *line);
void				cend(t_read *line);
void				chome(t_read *line);
int					ft_getch(void);
int					ft_windowsize(t_winsz *winsz);
void				ft_delete_char(t_read *read, int key);
void				ft_insert_char(t_read *read, int key);
int					tc_putc(int c);
void				feed_line(t_read *line, char *entry);
char				*ft_history(char *num);

void				add_history(char *entry);
void				old_hist_entry(t_read *read, t_dlist **hist);
void				new_hist_entry(t_read *read, t_dlist **hist);
t_dlist				*get_history(void);

void				raw_mode(void);
void				default_mode(void);
char				*env_getenv(char *key);

void				free_ptr(char **ptr);
void				ft_free_join(char **holder, char *s1, char *s2);
char				*free_dup(char *dest, char *src);

void				input_loop(t_read *line);
char				*reader(t_read *line);
char				*ft_read(void);

void				insert_auto(t_read *line, char *entry);

void				scroll_up(t_read *line);
int					read_u(t_read *line, int key_pressed);
int					autocomplete(t_read *line);
int					echo_auto(t_read *line, char *opt);
char				*ft_sstrcpy(char *dest, char *src);
int					copy_paste(t_read *line, int key_pressed);

char				*glob_files(char *match);
int					match(char *s1, char *s2);
int					glob_match(char *pat, char *str);
char				*glob_replace(char *str);

char				*get_bins(char *match);
char				*auto_files(char *match);

#endif
