/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/30 15:11:09 by gpetrov           #+#    #+#             */
/*   Updated: 2013/12/31 16:26:34 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <fcntl.h>
# include "libft/includes/libft.h"

typedef struct		s_data
{
	char			*name1;
	char			*name2;
	char			**av1;
	char			**av2;
	char			**argv;
	char			**env;
	int				i;
	int				j;
	char			*infile;
	char			*outfile;
	char			*cmd_1;
	char			*cmd_2;
	pid_t			pid;
	int				fd1[2];
	int				ret;
	int				fdes1;
	int				fdes2;
}					t_data;

void	ft_get_cmd(t_data *data, char **av);
int		ft_exec_cmd(t_data *data);
int		ft_count_c(char *str, char c);
char	**ft_get_path(char **tab);
int		ft_exec(t_data *data, char *str, char **opt);

#endif
