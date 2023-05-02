/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:58:56 by ccamargo          #+#    #+#             */
/*   Updated: 2023/05/02 17:18:46 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*form_tested_path(t_token *token, char *path)
{
	char	*tested_path;
	char	*tested_path_tmp;

	tested_path = ft_strjoin(path, "/");
	tested_path_tmp = tested_path;
	tested_path = ft_strjoin(tested_path, token->cmd[0]);
	ft_freethis(&tested_path_tmp, NULL);
	return (tested_path);
}

/* Run a binary based on a relative path. */

static void	run_path(t_shell *shell, t_token *token)
{
	int	i;

	i = 0;
	if (!access(token->cmd[0], F_OK))
	{
		execve(token->cmd[0], token->cmd, shell->envp);
	}
	else
	{
		command_not_found(shell, token->cmd[0]);
	}
	i++;
}

/* Run a binary based on envp. */

static void	run_sys_bin(t_shell *shell, t_token *token)
{
	char	*tested_path;
	int		i;

	i = 0;
	while (shell->paths[i])
	{
		tested_path = form_tested_path(token, shell->paths[i]);
		if (!access(tested_path, F_OK))
		{
			execve(tested_path, token->cmd, shell->envp);
			break ;
		}
		ft_freethis(&tested_path, NULL);
		i++;
	}
	if (tested_path == NULL)
		command_not_found(shell, token->cmd[0]);
	ft_freethis(&tested_path, NULL);
}

void	run_command(t_tk_exec *exec_vars, t_shell *shell)
{
	pid_t	pid;

	if (check_built_in(exec_vars->token, shell) != 0)
	{
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			close(exec_vars->fd[0]);
			if (!ft_strncmp(exec_vars->token->cmd[0], ".", 1) || \
			!ft_strncmp(exec_vars->token->cmd[0], "/", 1))
				run_path(shell, exec_vars->token);
			else
				run_sys_bin(shell, exec_vars->token);
			exit(EXIT_FAILURE);
		}
		else
			wait(&shell->exit_status);
	}
}