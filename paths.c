/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 17:45:37 by cboutier          #+#    #+#             */
/*   Updated: 2021/07/20 14:39:27 by cboutier         ###   ########.fr       */
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
			if (paths == NULL)
				ft_free_tab(paths);
			break ;
		}
		i++;
	}
	return (paths);
}

int	check_path1(char **envp, t_cmds *cmds)
{
	char	**paths1;
	char	*tmp;
	int		i;

	i = 0;
	if (*cmds->cmd1 == NULL)
		return (127);
	paths1 = ft_get_path(envp);
	if (!paths1)
		return (print_file_error(*cmds->cmd1));
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
	return (ft_free_tab(paths1));
}

int	check_path2(char **envp, t_cmds *cmds)
{
	char	**paths2;
	char	*tmp;
	int		i;

	i = 0;
	if (*cmds->cmd2 == NULL)
		return (127);
	paths2 = ft_get_path(envp);
	if (!paths2)
		return (print_file_error(*cmds->cmd2));
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
	return (ft_free_tab(paths2));
}
