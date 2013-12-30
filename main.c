/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/30 15:07:54 by gpetrov           #+#    #+#             */
/*   Updated: 2013/12/30 23:13:44 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>
#include <memory.h>
#include <unistd.h>

int		ft_count_c(char *str, char c)
{
	int		i;
	int		j;

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

void		ft_get_cmd(t_data *data, char **av)
{
	data->infile = av[1];
	data->outfile = av[4];
	data->cmd_1 = av[2];
	data->cmd_2 = av[3];
}

char	**ft_get_path(char **tab)
{
	char	**path;
	char	**tmp;
	int		i;
	int		j;

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

int		ft_exec(t_data *data)
{
	char	*tmp;
	char	**path;
	int		i;
	int		t;

	path = ft_get_path(data->env);
	i = 0;
	while (path[i] != 0)
	{
		tmp = ft_strjoin(path[i], data->cmd_2);
		t = access(tmp, X_OK);
		execve(tmp, data->argv, data->env);
		free(tmp);
		i++;
	}
	return (0);
}


int     redir(char *filename)
{
	int   fd;

	if (filename == NULL)
		return -1;
	fd = open(filename, O_RDONLY, 0644);
	if (fd == -1)
		return -1;
	return dup2(fd, STDIN_FILENO);
}

/* int		ft_exec_cmd(t_data *data) */
/* { */
/* 	pipe(data->fd1); */
/* 	/\* pipe(data->fd2); *\/ */
/* 	/\* data->pid = fork(); *\/ */
/* 	if (fork() == 0) */
/* 	{ */
/* 		close(1); */
/* 		dup(data->fd1[1]); */
/* 		close(data->fd1[0]); */
/* 		close(data->fd1[1]); */
/* 		execlp(data->cmd_1, data->cmd_1, NULL); */
/* 		exit(1); */
/* 	} */
/* 	if (fork() == 0) */
/* 	{ */
/* 		close(0); */
/* 		dup(data->fd1[0]); */
/* 		close(data->fd1[1]); */
/* 		close(data->fd1[0]); */
/* 		execlp(data->cmd_2, data->cmd_2, NULL); */
/* 	} */
/* 	close(data->fd1[0]); */
/* 	close(data->fd1[1]); */
/* 	wait(0); */
/* 	wait(0); */
/* 	return (0); */
/* } */

int		ft_exec_cmd(t_data *data)
{
	pipe(data->fd1);
	data->fd1[0] = open(data->infile, O_RDONLY, 0644);
	data->pid = fork();
	if (data->pid == 0)
	{
		/* close(data->fd1[1]); */
		dup2(data->fd1[0], 0);
		close(data->fd1[0]);
		execlp(data->cmd_2, data->cmd_2, NULL);
	}
	if (data->pid > 0)
	{
		data->fd1[1] = open(data->outfile, O_CREAT|O_WRONLY, 0666);
		/* close(data->fd1[0]); */
		dup2(data->fd1[1], 1);
		close(data->fd1[1]);
		execlp(data->cmd_1, data->cmd_1, NULL);
	}
	return (0);
}

int		main(int ac, char **av, char **env)
{
	t_data	data;

	data.env = env;
	if (ac == 5)
	{
		ft_get_cmd(&data, av);
		ft_exec_cmd(&data);
	}
	return (0);
}


/* int main() */
/* { */
/*     int file = open("pwd", O_CREAT|O_WRONLY, 0666); */
/* 	 dup2(file, 1); */
/*      close(file); */
/*      execlp("ls", "ls", NULL); */
/* 	 return (0); */
/* } */
