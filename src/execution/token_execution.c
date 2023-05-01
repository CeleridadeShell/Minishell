/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarecho <mcarecho@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:17:44 by ccamargo          #+#    #+#             */
/*   Updated: 2023/05/01 17:44:30 by mcarecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*form_tested_path(t_token *token,char *path)
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
//	int		child_pid;
	int		i;

	i = 0;
	if (!access(token->cmd[0], F_OK))
	{
/* 		child_pid = fork();
		if (child_pid == 0)
		{ */
			execve(token->cmd[0], token->cmd, shell->envp);
/* 		}
		waitpid(child_pid, NULL, 0); */
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
//	int		child_pid;
	int		i;

	i = 0;
	while (shell->paths[i])
	{
		tested_path = form_tested_path(token, shell->paths[i]);
		if (!access(tested_path, F_OK))
		{
/* 			child_pid = fork();
			if (child_pid == 0)
			{ */
				execve(tested_path, token->cmd, shell->envp);
/* 			}
			waitpid(child_pid, NULL, 0); */
			break ;
		}
		ft_freethis(&tested_path, NULL);
		i++;
	}
	if (tested_path == NULL)
		command_not_found(shell, token->cmd[0]);
	ft_freethis(&tested_path, NULL);
}

void	execute_token(t_shell *shell)
{
	t_token	*token;
	int		fd[2];
	int		fd_original[2];
 	pid_t	pid;
 	int		fd_in = 0;
	int		cmd_i;
	token = shell->h_token;
	cmd_i = 0;
	fd_original[0] = dup(STDIN_FILENO);
	fd_original[1] = dup(STDOUT_FILENO);
	while (cmd_i < shell->h_token->n_cmds)
    {
		if (token->type == WORD)
		{

			pipe(fd);
			if (fd_in != 0)
			{
				if (dup2(fd_in, STDIN_FILENO) == -1)
				{
					printf("Deu bosta!\n");
				}
			}
			if (token->next_token == NULL)
			{
				if (dup2(fd_original[1], STDOUT_FILENO) == -1)
				{
					printf("Deu bosta!\n");
				}
			}
			else
			{
				if (dup2(fd[1], STDOUT_FILENO) == -1)
				{
					printf("Deu bosta!\n");
				}
			}
			if (check_built_in(token, shell) != 0)
			{
				pid = fork();
				if (pid == -1)
					exit(EXIT_FAILURE);
				else if (pid == 0)
				{
					close(fd[0]);
					if (!ft_strncmp(token->cmd[0], ".", 1) || !ft_strncmp(token->cmd[0], "/", 1))
						run_path(shell, token);
					else
						run_sys_bin(shell, token);
					exit(EXIT_FAILURE);
				}
				else
				{
					wait(NULL);
				}
			}
			if (fd_in != 0)
			{
				close(fd_in);
			}
			fd_in = fd[0];
			close(fd[1]);
			cmd_i++;
		}
		else if (token->type == REDIRECT) {
			token = token->next_token;
		}
		token = token->next_token;
    }
	if (dup2(fd_original[0], STDIN_FILENO) == -1)
	{
		printf("Deu bosta!\n");
	}
	/* if (token->n_cmds == cmd_i)
	{
		dup2(fd_original[0], STDIN_FILENO);
	} */
}
