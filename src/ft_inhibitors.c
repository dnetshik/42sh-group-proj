/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inhibitors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmanamel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 09:30:41 by qmanamel          #+#    #+#             */
/*   Updated: 2017/10/01 09:30:52 by qmanamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static int		ends_with(char *s, char c)
{
	int i;
	int	f;

	i = 0;
	f = 0;
	while (s[i])
	{
		if (s[i] == c)
			f++;
		i++;
	}
	if (f % 2)
		return (1);
	return (0);
}

char			*ignore(char *s, char c)
{
	int			i;
	int			j;
	char		*ret;

	i = -1;
	j = 0;
	while (s[++i])
	{
		if (s[i] != c)
			j++;
	}
	ret = (char *)malloc(sizeof(char) * j + 1);
	i = -1;
	j = 0;
	while (s[++i])
	{
		if (s[i] != c)
			ret[j++] = s[i];
	}
	ret[j] = '\0';
	return (ret);
}

char			*d_quote(char *cmd)
{
	char	*buf;
	char	*join;

	join = ft_strdup(" ");
	if (ends_with(cmd, '"'))
	{
		if (cmd[1])
			join = ft_strjoin(cmd, "\n");
		while (1)
		{
			ft_putstr("dquote> ");
			buf = ft_read();
			buf = ft_strjoin(buf, "\n");
			join = ft_strjoin(join, buf);
			if (!ends_with(join, '"'))
				break ;
			free(buf);
		}
		join = ignore(join, '"');
		return (join);
	}
	else
		return (cmd);
}

char			*s_quote(char *cmd)
{
	char	*buf;
	char	*join;

	join = ft_strdup(" ");
	if (ends_with(cmd, '\''))
	{
		if (cmd[1])
			join = ft_strjoin(cmd, "\n");
		while (1)
		{
			ft_putstr("quote> ");
			buf = ft_read();
			buf = ft_strjoin(buf, "\n");
			join = ft_strjoin(join, buf);
			if (!ends_with(join, '\''))
				break ;
			free(buf);
		}
		join = ignore(join, '\'');
		return (join);
	}
	else
		return (cmd);
}

char			*backslash(char *cmd)
{
	char	*buf;
	char	*join;

	join = ft_strdup(" ");
	if (ends_with(cmd, '\\'))
	{
		if (cmd[1])
			join = ft_strjoin(cmd, "\n");
		while (1)
		{
			ft_putstr("> ");
			buf = ft_read();
			buf = ft_strjoin(buf, "\n");
			join = ft_strjoin(cmd, buf);
			free(buf);
			join = ignore(join, '\\');
			return (join);
		}
	}
	else
		return (cmd);
}
