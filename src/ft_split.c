/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmanamel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 13:34:54 by qmanamel          #+#    #+#             */
/*   Updated: 2017/09/28 13:35:29 by qmanamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static int		special(char *s, int *k)
{
	int i;
	int j;
	int c;

	i = 0;
	j = 0;
	c = 0;
	if (s[i] == '"' || s[i] == '\'')
	{
		c = s[i++];
		while (s[i] && s[i] != c)
			i++;
		if (s[i++] == c)
			j++;
	}
	*k += i;
	return (j);
}

static int		split_c(char *s)
{
	int count;
	int i;
	int f;

	count = 0;
	i = 0;
	while (s[i])
	{
		f = 0;
		while (s[i] == ' ')
			i++;
		count += special(&s[i], &i);
		while (s[i] && s[i] != '"' && s[i] != '\'' && s[i] != ' ')
		{
			i++;
			f = 1;
		}
		count += f;
	}
	return (count);
}

static int		wordlen(char *s, char d)
{
	int i;
	int c;
	int len;

	i = 0;
	c = 0;
	len = 0;
	while (s[i] && s[i] != d)
	{
		while (s[i] == d)
			len++ ? i++ : i++;
		if (s[i] == '"' || s[i] == '\'')
		{
			c = s[i++];
			while (s[i] && s[i] != c)
				len++ ? i++ : i++;
			len++;
		}
		while (s[i] && s[i] != d)
		{
			len++;
			i++;
		}
	}
	return (len);
}

char			*trim(char *s)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != '"' && s[i] != '\'')
			j++;
		i++;
	}
	ret = malloc(sizeof(char) * (j + 1));
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != '"' && s[i] != '\'')
			ret[j++] = s[i];
		i++;
	}
	ret[j] = '\0';
	return (ret);
}

char			**ft_shellsplit(char *s, char d)
{
	char	**ret;
	char	*tmp;
	int		i;
	int		k;

	i = split_c(s);
	k = 0;
	ret = (char **)malloc(sizeof(char *) * i + 1);
	ret[i] = NULL;
	while (i--)
	{
		while (*s && *s == d)
			s++;
		if (d == ' ')
		{
			tmp = ft_strsub(s, 0, wordlen(s, d));
			ret[k++] = trim(tmp);
			free(tmp);
		}
		else
			ret[k++] = ft_strsub(s, 0, wordlen(s, d));
		s += wordlen(s, d);
	}
	return (ret);
}
