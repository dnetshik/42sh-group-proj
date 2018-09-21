/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmanamel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/30 13:00:38 by qmanamel          #+#    #+#             */
/*   Updated: 2017/10/01 10:33:45 by qmanamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <fcntl.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <dirent.h>
# include <pwd.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include "../src/ft_read/line.h"
# define BUFF_SIZE 1024
# define CLEAR "\e[1;1H\e[2J"
# define SETENV_SYNTAX "\e[0;1m\e[0;32msyntax error: [Key] [Value]\e[0;0m"
# define ENV_ERROR_1 "\e[0;31mNot found , try [setenv]\e[1;0m"
# define FILE_IN 1
# define FILE_OUT 2
# define FILE_APPEND 3
# define HEREDOC 4
# define CMD_SUCCESS 1
# define CMD_FALUIRE 0

struct termios term;
struct termios oterm;
typedef struct	s_red
{
	char		**command;
	int			opt;
	char		*files;
	char		**f_files;
}				t_red;

typedef struct	s_shell
{
	char		**g_env;
	int			ret_val;
	int			curr_fd;
	int			p[2];
	int			fd_in;
	int			log_ret;
	int			g_local_i;
	int			g_local_j;
	t_red		*red;
}				t_shell;

t_shell			*g_shell;
char			**g_local;
struct termios	g_tattr;

void			prog_handle(int sign_n);
void			proc_handler(int sign_n);
void			exit_shell(void);
int				exec_command_env(void);
void			new_env(void);
int				ft_check_file(char *str, int *ret);
int				unsetenv_builtin(char **args);
void			display_prompt(void);
int				pipe_parse(char *command);
int				exec_pipe(char **str, int len);
char			*ft_getenv(char *s_envstr);
int				exec_command(char **cmd);
int				parse_input(char **input);
int				exec_command_main(char **command);
int				run_cmds(char **commands);
void			exec_cd(char *dir, int old_pwd_bool);
int				read_history(void);
int				cm_echo(char **s);
void			proccess_handler(int sign_n);
void			execve_pipe(char ***cmd);
void			exit_handler(int n);
int				with_pipe_execute(char *str);
int				red_parse(char *str);
int				exec_red(char **str, int len);
int				exec_command_cd(char **dir);
int				exec_command_echo(char **line);
char			*ignore(char *s, char c);
int				exec_shell_cmd(char *path, char **args);
int				exec_command_setenv(char **g_shell);
void			set_env(char *key, char *value);
int				logical_op_parse(char *str);
char			**ft_shellsplit(char *s, char d);
char			*find_str(char *str, int len);
char			*ft_match(char *s);
int				local_match(char *s);
void			add_local(char *s);
char			**set_vars(char **ptr);
int				export(char *key);
int				ft_unset(char *val);
char			*d_quote(char *cmd);
char			*s_quote(char *cmd);
char			*backslash(char *cmd);

#endif
