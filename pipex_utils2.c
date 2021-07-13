/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:54:17 by cboutier          #+#    #+#             */
/*   Updated: 2021/07/13 11:34:33 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

void	ft_free_cmds(t_cmds *cmds)
{
	ft_free_tab(cmds->cmd1);
	ft_free_tab(cmds->cmd2);
	free(cmds->cmd1_w_path);
	free(cmds->cmd2_w_path);
}

int		print_ret_err(int error, int i, t_cmds *cmds)
{
	if (error == E_PIPE_FAILED)
		write(STDOUT_FILENO, "pipe failed\n", 12);
	else if (error == E_FORK_FAILED)
		write(STDOUT_FILENO, "fork failed\n", 12);
	else if (error == E_CMD_NOT_FOUND && i == 1)
	{
		ft_putstr_fd(*cmds->cmd1, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(1);
	}
	else if (error == E_CMD_NOT_FOUND && i == 2)
	{
		ft_putstr_fd(*cmds->cmd2, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(1);
	}
	return (error);
}
