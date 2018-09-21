/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_bins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmanamel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 12:18:55 by qmanamel          #+#    #+#             */
/*   Updated: 2017/09/25 08:36:15 by qmanamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line.h"

static void		add_builtins(char **buff, char *match)
{
	if (ft_strncmp(match, "setenv", ft_strlen(match)) == 0)
		ft_free_join(buff, *buff, "setenv");
	if (ft_strncmp(match, "exit", ft_strlen(match)) == 0)
		ft_free_join(buff, *buff, "exit");
	if (ft_strncmp(match, "unsetenv", ft_strlen(match)) == 0)
		ft_free_join(buff, *buff, "unsetenv");
	if (ft_strncmp(match, "env", ft_strlen(match)) == 0)
		ft_free_join(buff, *buff, "env");
	if (ft_strncmp(match, "unset", ft_strlen(match)) == 0)
		ft_free_join(buff, *buff, "unset");
	if (ft_strncmp(match, "history", ft_strlen(match)) == 0)
		ft_free_join(buff, *buff, "history");
	if (ft_strncmp(match, "cd", ft_strlen(match)) == 0)
		ft_free_join(buff, *buff, "cd");
}

static void		add_local_bins(char **ret, char *match)
{
	DIR				*dirp;
	struct dirent	*entry;

	if ((dirp = opendir(".")) && (ft_strncmp(match, "./", 2) == 0))
	{
		while ((entry = readdir(dirp)) != NULL)
		{
			if ((ft_strncmp(entry->d_name, match + 2, ft_strlen(match + 2))
						== 0) && (access(entry->d_name, X_OK) == 0))
			{
				ft_free_join(ret, *ret, "./");
				ft_free_join(ret, *ret, entry->d_name);
				ft_free_join(ret, *ret, " ");
			}
		}
	}
}

static void		loop_add(DIR *dirp, char **ret, char *match)
{
	struct dirent	*entry;

	while ((entry = readdir(dirp)) != NULL)
	{
		if (ft_strncmp(entry->d_name, match, ft_strlen(match)) == 0)
		{
			ft_free_join(ret, *ret, entry->d_name);
			ft_free_join(ret, *ret, " ");
		}
	}
	closedir(dirp);
}

static char		**get_paths(void)
{
	char	**paths;
	char	*key;

	key = env_getenv("PATH");
	paths = ft_strsplit(key, ':');
	free(key);
	return (paths);
}

char			*get_bins(char *match)
{
	char			**paths;
	int				i;
	DIR				*dirp;
	char			*ret;

	paths = get_paths();
	i = 0;
	ret = ft_strdup(" ");
	while (paths[i])
	{
		dirp = opendir(paths[i]);
		if (dirp != NULL)
			loop_add(dirp, &ret, match);
		i++;
	}
	add_local_bins(&ret, match);
	add_builtins(&ret, match);
	closedir(dirp);
	return (ret);
}
