/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 08:55:34 by cboutier          #+#    #+#             */
/*   Updated: 2021/07/13 11:40:52 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_prgm(t_cmds *cmds, char **av, char **envp)
{
	parsing(av, cmds);
	check_path1(envp, cmds);
	check_path2(envp, cmds);
}

pid_t	fork_pid1(t_cmds *cmds, int *pfd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		print_ret_err(E_FORK_FAILED, 0, cmds);
	if (pid == CHILD)
		exec1(cmds, pfd, envp);
	else
		close(pfd[1]);
	return (pid);
}

pid_t	fork_pid2(t_cmds *cmds, int *pfd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		print_ret_err(E_FORK_FAILED, 0, cmds);
	if (pid == CHILD)
		exec2(cmds, pfd, envp);
	else
		close(pfd[0]);
	return (pid);
}

int	ft_wait_pid(pid_t pid1, pid_t pid2)
{
	int	status;
	int exit_code;

	exit_code = 0;
	waitpid(pid1, &status, 0);
	if (WIFEXITED(status))
		exit_code = (WEXITSTATUS(status));
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		exit_code = (WEXITSTATUS(status));
	return (exit_code);
}

int	main(int ac, char **av, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;
	int		pfd[2];
	t_cmds	cmds;
	// int		status;
	int		exit_code;

	if (ac != 5)
	{
		ft_putstr_fd("Usage : ./pipex infile cmd1 cmd2 outfile\n", 2);
		exit(1);
	}
	exit_code = 0;
	init_cmds(&cmds);
	init_prgm(&cmds, av, envp);
	if (pipe(pfd) == -1)
		print_ret_err(E_PIPE_FAILED, 0, &cmds);
	pid1 = fork_pid1(&cmds, pfd, envp);
	pid2 = fork_pid2(&cmds, pfd, envp);
	exit_code = ft_wait_pid(pid1, pid2);
	/* waitpid(pid1, &status, 0);
	if (WIFEXITED(status))
		exit_code = (WEXITSTATUS(status));
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		exit_code = (WEXITSTATUS(status)); */
	ft_free_cmds(&cmds);
	return (exit_code);
}
