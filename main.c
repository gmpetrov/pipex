/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/30 15:07:54 by gpetrov           #+#    #+#             */
/*   Updated: 2013/12/31 16:26:46 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		ft_exec_cmd(t_data *data)
{
	data->fdes1 = open(data->infile, O_RDONLY);
	data->fdes2 = open(data->outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
	pipe(data->fd1);
	data->pid = fork();
	if (data->pid == 0)
	{
		close(data->fd1[0]);
		dup2(data->fd1[1], 1);
		dup2(data->fdes1, 0);
		ft_exec(data, data->name1, data->av1);
		close(data->fd1[0]);
	}
	if (data->pid > 0)
	{
		close(data->fd1[1]);
		dup2(data->fd1[0], 0);
		dup2(data->fdes2, 1);
		ft_exec(data, data->name2, data->av2);
		close(data->fd1[1]);
	}
	return (0);
}

int		main(int ac, char **av, char **env)
{
	t_data	data;

	if (env[0] == NULL)
		return (0);
	data.env = env;
	if (ac == 5)
	{
		ft_get_cmd(&data,  av);
		ft_exec_cmd(&data);
	}
	return (0);
}
