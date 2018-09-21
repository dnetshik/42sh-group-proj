/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmanamel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 10:29:26 by qmanamel          #+#    #+#             */
/*   Updated: 2017/09/25 09:13:38 by qmanamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line.h"

static char		*ft_curlytrim(char *s)
{
	char	*tr;
	char	*ret;
	int		i;

	if (!s)
		return (NULL);
	tr = ft_strdup(s);
	if (!tr)
		return (NULL);
	else
	{
		i = 0;
		while (tr[i] == '{')
			i++;
		tr = ft_strcpy(tr, tr + i);
		i = ft_strlen(tr) - 1;
		while ((tr[i] == '}') && i >= 0)
		{
			tr[i] = '\0';
			i--;
		}
		ret = ft_strdup(tr);
		free(tr);
		return (ret);
	}
}

static void		curly_glob(char **ret, char *pat)
{
	char	**pats;
	int		i;
	char	*tmp;
	char	*fr;

	fr = ft_curlytrim(pat);
	pats = ft_strsplit(fr, ',');
	free(fr);
	i = 0;
	while (pats[i])
	{
		tmp = glob_files(pats[i]);
		if (ft_strlen(tmp))
			ft_free_join(ret, *ret, tmp);
		else
			ft_free_join(ret, *ret, pats[i]);
		ft_free_join(ret, *ret, " ");
		free(tmp);
		i++;
	}
	free_ptr(pats);
}

static void		normal_glob(char **ret, char *cur)
{
	char *tmp;
	char *tr;

	tr = glob_files(cur);
	tmp = ft_strtrim(tr);
	free(tr);
	if (ft_strlen(tmp))
		ft_free_join(ret, *ret, tmp);
	else
		ft_free_join(ret, *ret, cur);
	ft_free_join(ret, *ret, " ");
	free(tmp);
}

char			*glob_replace(char *str)
{
	char	**ar;
	char	*ret;
	int		i;

	ret = ft_strtrim(str);
	i = ft_strlen(ret);
	free(ret);
	if (!i)
		return (str);
	ar = ft_strsplit(str, ' ');
	i = 0;
	ret = ft_strdup(" ");
	while (ar[i])
	{
		if (ar[i][0] == '{')
			curly_glob(&ret, ar[i]);
		else
			normal_glob(&ret, ar[i]);
		i++;
	}
	free(str);
	free_ptr(ar);
	return (ret);
}
