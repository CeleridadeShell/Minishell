/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:17:44 by ccamargo          #+#    #+#             */
/*   Updated: 2023/04/25 18:02:09 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*form_tested_path(t_token *token, int i)
{
	char	*tested_path;
	char	*tested_path_tmp;

	tested_path = ft_strjoin(token->paths[i], "/");
	tested_path_tmp = tested_path;
	tested_path = ft_strjoin(tested_path, token->cmd[0]);
	ft_freethis(&tested_path_tmp, NULL);
	return (tested_path);
}

/* Run a binary based on a relative path. */

static void	run_path(t_shell *shell, t_token *token)
{
	int		child_pid;
	int		i;

	i = 0;
	if (!access(token->cmd[0], F_OK))
	{
		child_pid = fork();
		if (child_pid == 0)
		{
			execve(token->cmd[0], token->cmd, shell->envp);
		}
		waitpid(child_pid, NULL, 0);
	}
	i++;
}

/* Run a binary based on envp. */

static void	run_sys_bin(t_shell *shell, t_token *token)
{
	char	*tested_path;
	int		child_pid;
	int		i;

	i = 0;
	while (token->paths[i])
	{
		tested_path = form_tested_path(token, i);
		if (!access(tested_path, F_OK))
		{
			child_pid = fork();
			if (child_pid == 0)
			{
				execve(tested_path, token->cmd, shell->envp);
			}
			waitpid(child_pid, NULL, 0);
			break ;
		}
		ft_freethis(&tested_path, NULL);
		i++;
	}
	ft_freethis(&tested_path, NULL);
}

void	execute_token(t_shell *shell)
{
	t_token	*token;

	token = shell->h_token;
	if (!ft_strncmp((char *) token->cmd[0], "exit", 4))
	{
		shell->exit_status = 1;
		return ;
	}
	//check_built_in(cmd, shell);
	/* if (!cmd->builtin)
	{ */
		if (!ft_strncmp(token->cmd[0], ".", 1) || !ft_strncmp(token->cmd[0], "/", 1))
			run_path(shell, token);
		else
			run_sys_bin(shell, token);
	/* } */
}