/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 17:45:37 by cboutier          #+#    #+#             */
/*   Updated: 2021/07/13 10:53:33 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_get_path(char **envp)
{
	int		i;
	char	**paths;

	paths = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			break ;
		}
		i++;
	}
	return (paths);
}

/* void check_path(char **envp, t_cmds *cmds)
{
	char **paths;
	char *tmp;
	int i;

	i = 0;
	tmp = NULL;
	paths = ft_get_path(envp);
	if (!paths)
		exit(1);
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = ft_strjoin(tmp, cmds->cmd1[0]);

		if (access(paths[i], F_OK) == 0)
		{
			cmds->cmd1_w_path = ft_strdup(paths[i]);
			break;
		}
		else
			i++;
		ft_free_tab(paths);
		paths = ft_get_path(envp);
		paths[i] = ft_strjoin(tmp, cmds->cmd2[0]);
		free(tmp);
		tmp = NULL;
		if (access(paths[i], F_OK) == 0)
		{
			cmds->cmd2_w_path = ft_strdup(paths[i]);
			break;
		}
		else
			i++;
	}
	ft_free_tab(paths);
} */

void	check_path1(char **envp, t_cmds *cmds)
{
	char	**paths1;
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	paths1 = ft_get_path(envp);
	if (!paths1)
		exit(1);
	if (ft_strchr(cmds->cmd1[0], '/') != 0)
		print_ret_err(E_CMD_NOT_FOUND, 1, cmds);
	while (paths1[i])
	{
		tmp = ft_strjoin(paths1[i], "/");
		free(paths1[i]);
		paths1[i] = ft_strjoin(tmp, cmds->cmd1[0]);
		free(tmp);
		if (access(paths1[i], F_OK) == 0)
		{
			cmds->cmd1_w_path = ft_strdup(paths1[i]);
			break ;
		}
		i++;
	}
	ft_free_tab(paths1);
}

void	check_path2(char **envp, t_cmds *cmds)
{
	char	**paths2;
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	paths2 = ft_get_path(envp);
	if (!paths2)
		exit(1);
	if (ft_strchr(cmds->cmd2[0], '/') != 0)
		print_ret_err(E_CMD_NOT_FOUND, 2, cmds);
	while (paths2[i])
	{
		tmp = ft_strjoin(paths2[i], "/");
		free(paths2[i]);
		paths2[i] = ft_strjoin(tmp, cmds->cmd2[0]);
		free(tmp);
		if (access(paths2[i], F_OK) == 0)
		{
			cmds->cmd2_w_path = ft_strdup(paths2[i]);
			break ;
		}
		i++;
	}
	ft_free_tab(paths2);
}
