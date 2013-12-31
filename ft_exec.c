/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/31 15:42:22 by gpetrov           #+#    #+#             */
/*   Updated: 2013/12/31 15:46:35 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_count_c(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != 0)
	{
		if (str[i] == c)
			j++;
		i++;
	}
	return (j);
}

void	ft_get_cmd(t_data *data, char **av)
{
	char	**tab1;
	char	**tab2;

	tab1 = ft_strsplit(av[2], ' ');
	tab2 = ft_strsplit(av[3], ' ');
	data->infile = av[1];
	data->outfile = av[4];
	data->cmd_1 = av[2];
	data->cmd_2 = av[3];
	data->name1 = tab1[0];
	data->name2 = tab2[0];
	data->av1 = tab1;
	data->av2 = tab2;
}

char	**ft_get_path(char **tab)
{
	char	**path;
	char	**tmp;
	int	i;
	int	j;

	tmp = ft_strsplit(tab[0] + 5, ':');
	i = ft_count_c(tab[0], ':') + 1;
	path = (char **)malloc(i * sizeof(*path));
	path[i] = 0;
	j = 0;
	while (j < i)
	{
		path[j] = ft_strjoin(tmp[j], "/");
		free(tmp[j]);
		j++;
	}
	free(tmp);
	return (path);
}

int	ft_exec(t_data *data, char *str, char **opt)
{
	char	*tmp;
	char	**path;
	int	i;
	int	t;

	path = ft_get_path(data->env);
	i = 0;
	while (path[i] != 0)
	{
		tmp = ft_strjoin(path[i], str);
		t = access(tmp, X_OK);
		execve(tmp, opt, data->env);
		free(tmp);
		i++;
	}
	return (0);
}
