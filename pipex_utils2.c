/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:54:17 by cboutier          #+#    #+#             */
/*   Updated: 2021/07/20 14:40:21 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	print_ret_err(int error, int i, t_cmds *cmds)
{
	if (error == E_PIPE_FAILED)
		write(STDERR_FILENO, "pipe failed\n", 12);
	else if (error == E_FORK_FAILED)
		write(STDERR_FILENO, "fork failed\n", 12);
	else if (error == E_CMD_NOT_FOUND && i == 1)
	{
		ft_putstr_fd(*cmds->cmd1, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		ft_free_tab(cmds->cmd1);
		exit(127);
	}
	else if (error == E_CMD_NOT_FOUND && i == 2)
	{
		ft_putstr_fd(*cmds->cmd2, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		ft_free_tab(cmds->cmd1);
		ft_free_tab(cmds->cmd2);
		exit(127);
	}
	return (error);
}

void	print_errno(char *s_cmds)
{
	ft_putstr_fd(s_cmds, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

int	print_file_error(char *s_cmds)
{
	ft_putstr_fd(s_cmds, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	return (1);
}

void	print_cmd_error(char *s_cmds)
{
	ft_putstr_fd(s_cmds, 2);
	ft_putstr_fd(": Command not found\n", STDERR_FILENO);
}
