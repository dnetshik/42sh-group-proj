/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmanamel <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 13:50:34 by qmanamel          #+#    #+#             */
/*   Updated: 2017/09/25 08:41:56 by qmanamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line.h"

static int		hist_len(void)
{
	char	**s;
	int		len;
	char	buff[MAX_CMD_LEN * 3];
	int		fd;

	len = 0;
	fd = open(g_path, O_RDONLY);
	len = read(fd, buff, (MAX_CMD_LEN * 3));
	close(fd);
	buff[len] = '\0';
	s = ft_strsplit(buff, '\n');
	len = 0;
	while (s[len])
		len++;
	return (len);
}

static char		*hist(char *val)
{
	char	**ptr;
	int		i;
	char	buff[MAX_CMD_LEN * 3];
	int		fd;

	ptr = malloc(sizeof(char *) * hist_len() + 1);
	fd = open(g_path, O_RDONLY);
	i = read(fd, buff, (MAX_CMD_LEN * 3));
	buff[i] = '\0';
	ptr = ft_strsplit(buff, '\n');
	close(fd);
	i = hist_len() - 1;
	while (ptr[i] && i >= 0)
	{
		if (ft_strncmp(ptr[i], val, ft_strlen(val)) == 0)
			return (ptr[i]);
		i--;
	}
	return (ft_strjoin("!", val));
}

static char		**hist_gnl(void)
{
	char	buff[MAX_CMD_LEN * 3];
	int		fd;
	int		i;
	char	**ret;

	fd = open(g_path, O_RDONLY);
	i = read(fd, buff, (MAX_CMD_LEN * 3));
	close(fd);
	buff[i] = '\0';
	ret = ft_strsplit(buff, '\n');
	return (ret);
}

char			*ft_history(char *num)
{
	int		i;
	int		n;
	char	**ret;

	i = 0;
	n = (num[1] == '!') ? hist_len() - 1 : ft_atoi(num + 1);
	n = (ft_strcmp(num, "!-1") == 0) ? hist_len() - 1 : n;
	if (!ft_isdigit(num[1]) && ft_isalpha(num[1]))
		return (hist(&num[1]));
	ret = hist_gnl();
	while (ret[i])
	{
		if (i == n)
			return (ret[i]);
		i++;
	}
	return (ft_strdup(num));
}
