/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 17:10:04 by cboutier          #+#    #+#             */
/*   Updated: 2021/07/09 17:50:32 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "pipex.h"

void	init_cmds(t_cmds *cmds)
{
	cmds->file1 = 0;
	cmds->cmd1 = 0;
	cmds->cmd2 = 0;
	cmds->file2 = 0;
}


void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
	  dprintf(2, "i = [%d] et tab = [%s]\n", i, tab[i]);
		i++;
	}
}

void	parsing(char **av, t_cmds *cmds)
{
	cmds->file1 = av[1];
	cmds->cmd1 = ft_split(av[2], ' ');
	print_tab(cmds->cmd1);
	cmds->cmd2 = ft_split(av[3], ' ');
	print_tab(cmds->cmd2);
	cmds->file2 = av[4];
}

void	exec1(t_cmds *cmds, int *pfd, char **envp)
{
	int	fd_in;

	fd_in = open(cmds->file1, O_RDONLY);
	if (fd_in == -1)
	{
		ft_putstr_fd(cmds->file1, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		exit(1);
	}
	close(pfd[0]);
	dup2(fd_in, STDIN_FILENO);
	dup2(pfd[1], STDOUT_FILENO);
	close(pfd[1]);
	close(fd_in);
	if (execve(*cmds->cmd1, cmds->cmd1, envp) == -1)
	{
		ft_putstr_fd(*cmds->cmd1, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(1);
	}
	exit(0);
}

void	exec2(t_cmds *cmds, int *pfd, char **envp)
{
	int	fd_out;

	fd_out = open(cmds->file2, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd_out == -1)
		exit(0);
	dup2(fd_out, STDOUT_FILENO);
	close(pfd[1]);
	dup2(pfd[0], STDIN_FILENO);
	close(pfd[0]);
	close(fd_out);
	if (execve(*cmds->cmd2, cmds->cmd2, envp) == -1)
	{
		ft_putstr_fd(*cmds->cmd2, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(1);
	}
}
