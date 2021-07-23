/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 16:15:30 by cboutier          #+#    #+#             */
/*   Updated: 2021/07/17 16:34:58 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_free_tab(char **tab)
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
	return (0);
}

void	ft_free_cmds(t_cmds *cmds)
{
	ft_free_tab(cmds->cmd1);
	ft_free_tab(cmds->cmd2);
	free(cmds->cmd1_w_path);
	free(cmds->cmd2_w_path);
}
