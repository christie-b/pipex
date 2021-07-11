/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 15:06:30 by cboutier          #+#    #+#             */
/*   Updated: 2021/07/09 18:07:20 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define CHILD 0
# define E_PIPE_FAILED 1
# define E_FORK_FAILED -1

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>

typedef struct s_cmds
{
	char	*file1;
	char	**cmd1;
	char	**cmd2;
	char	*file2;
}	t_cmds;

void	init_cmds(t_cmds *cmds);
void	init_prgm(t_cmds *cmds, char **av, char **envp);
char	**ft_split(char const *s, char c);
void	ft_putstr_fd(char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char *s1, char *s2);
void	parsing(char **av, t_cmds *cmds);
void	exec1(t_cmds *cmds, int *pfd, char **envp);
void	exec2(t_cmds *cmds, int *pfd, char **envp);
char	**ft_get_path(char **envp);
void	check_path1(char **envp, t_cmds *cmds);
void	check_path2(char **envp, t_cmds *cmds);
char	*ft_strchr(const char *str, int c);
int		print_ret_err(int error);
char	*ft_strdup(char *s);
void	ft_free_tab(char **tab);
size_t	ft_strlen(char *s);

#endif
