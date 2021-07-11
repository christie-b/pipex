/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 08:55:34 by cboutier          #+#    #+#             */
/*   Updated: 2021/07/09 18:10:49 by cboutier         ###   ########.fr       */
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

int	print_ret_err(int error)
{
	if (error == E_PIPE_FAILED)
		write(STDOUT_FILENO, "pipe failed\n", 12);
	else if (error == E_FORK_FAILED)
		write(STDOUT_FILENO, "fork failed\n", 12);
	return (error);
}

void	init_prgm(t_cmds *cmds, char **av, char **envp)
{
	//init_cmds(&cmds);
	parsing(av, cmds);
	(void)envp;
	//	check_path1(envp, cmds);
	//check_path2(envp, cmds);
}

int	main(int ac, char **av, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;
	int		pfd[2];
	t_cmds	cmds;
	int		status;

	if (ac != 5)
	{
		ft_putstr_fd("Usage : ./a.out infile cmd1 cmd2 outfile\n", 2);
		exit(1);
	}
	init_cmds(&cmds);
	init_prgm(&cmds, av, envp);

	// parsing(av, &cmds);
	 check_path1(envp, &cmds);
	 check_path2(envp, &cmds);
       	if (pipe(pfd) == -1)
		print_ret_err(E_PIPE_FAILED);
	pid1 = fork();
	if (pid1 == -1)
		print_ret_err(E_FORK_FAILED);
	if (pid1 == CHILD)
		exec1(&cmds, pfd, envp);
	else
		close(pfd[1]);
	waitpid(pid1, &status, 0);
	if (!WIFEXITED(status) && !WEXITSTATUS(status))
		exit(1);
	pid2 = fork();
	if (pid2 == -1)
		print_ret_err(E_FORK_FAILED);
	if (pid2 == CHILD)
		exec2(&cmds, pfd, envp);
	waitpid(pid2, &status, 0);
	ft_free_tab(cmds.cmd1);
	ft_free_tab(cmds.cmd2);
	cmds.cmd1 = NULL;
	if (!WIFEXITED(status) && !WEXITSTATUS(status))
		exit(1);

}
