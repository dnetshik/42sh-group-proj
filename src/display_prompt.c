/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmanamel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 12:21:01 by qmanamel          #+#    #+#             */
/*   Updated: 2017/09/25 16:04:13 by qmanamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char		*seven(char *ptr)
{
	char	*s;
	int		i;

	i = 0;
	s = ft_strnew(7);
	while (i < 7)
	{
		s[i] = ptr[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char		*git(void)
{
	int		fd;
	char	line[BUFF_SIZE];
	char	*ret;
	int		r;

	fd = open(".git/HEAD", O_RDONLY);
	if (fd != -1)
	{
		r = read(fd, line, BUFF_SIZE);
		line[r - 1] = '\0';
		close(fd);
		if (ft_strncmp("ref", line, 3) == 0)
		{
			ret = ft_strchr(line, '/') + 1;
			ret = ft_strdup(ft_strchr(ret, '/') + 1);
			return (ret);
		}
		ret = seven(line);
		return (ret);
	}
	return (ft_strdup(""));
}

void		display_prompt(void)
{
	char	*dir;
	char	*git_check;
	char	buff[BUFF_SIZE];

	git_check = git();
	dir = getcwd(buff, BUFF_SIZE);
	dir = ft_strrchr(dir, '/');
	ft_putstr("\x1b[1m-> : \x1b[32m(");
	ft_putstr(dir + 1);
	ft_putstr(")");
	if (!ft_isemptystr(git_check))
	{
		ft_putstr("\x1b[32m < ");
		ft_putstr(git_check);
		ft_putstr(" > \x1b[0m");
	}
	if (g_shell->ret_val == 0)
		ft_putstr("\x1b[32m % \x1b[0m");
	else
		ft_putstr("\x1b[31m % \x1b[0m");
}
