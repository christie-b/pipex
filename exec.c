/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 17:10:04 by cboutier          #+#    #+#             */
/*   Updated: 2021/07/20 14:44:52 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_cmds(t_cmds *cmds)
{
	cmds->file1 = 0;
	cmds->cmd1 = 0;
	cmds->cmd2 = 0;
	cmds->file2 = 0;
	cmds->cmd1_w_path = 0;
	cmds->cmd2_w_path = 0;
}

void	parsing(char **av, t_cmds *cmds)
{
	cmds->file1 = av[1];
	cmds->cmd1 = ft_split(av[2], ' ');
	if (cmds->cmd1 == NULL)
		exit(127);
	if (ft_strchr(cmds->cmd1[0], '/') != 0)
		print_ret_err(E_CMD_NOT_FOUND, 1, cmds);
	cmds->cmd2 = ft_split(av[3], ' ');
	if (cmds->cmd2 == NULL)
	{
		ft_free_tab(cmds->cmd1);
		exit(1);
	}
	if (ft_strchr(cmds->cmd2[0], '/') != 0)
		print_ret_err(E_CMD_NOT_FOUND, 2, cmds);
	cmds->file2 = av[4];
}

void	exec1(t_cmds *cmds, int *pfd, char **envp)
{
	int	fd_in;

	fd_in = open(cmds->file1, O_RDONLY);
	if (fd_in == -1)
	{
		print_errno(cmds->file1);
		ft_free_cmds(cmds);
		exit(1);
	}
	close(pfd[0]);
	if (dup2(fd_in, STDIN_FILENO) == -1 || dup2(pfd[1], STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("dup2 failed\n", 2);
		exit(1);
	}
	close(pfd[1]);
	close(fd_in);
	if (cmds->cmd1_w_path == NULL
		|| (execve(cmds->cmd1_w_path, cmds->cmd1, envp) == -1))
	{
		print_cmd_error(*cmds->cmd1);
		ft_free_cmds(cmds);
		exit(127);
	}
	exit(0);
}

void	exec2(t_cmds *cmds, int *pfd, char **envp)
{
	int	fd_out;

	fd_out = open(cmds->file2, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd_out == -1)
	{
		print_errno(cmds->file2);
		ft_free_cmds(cmds);
		exit(1);
	}
	dup2(fd_out, STDOUT_FILENO);
	close(pfd[1]);
	dup2(pfd[0], STDIN_FILENO);
	close(pfd[0]);
	close(fd_out);
	if (cmds->cmd2_w_path == NULL
		|| (execve(cmds->cmd2_w_path, cmds->cmd2, envp) == -1))
	{
		print_cmd_error(*cmds->cmd2);
		ft_free_cmds(cmds);
		exit(127);
	}
	exit(0);
}
