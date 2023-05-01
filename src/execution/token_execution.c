/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarecho <mcarecho@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:17:44 by ccamargo          #+#    #+#             */
/*   Updated: 2023/05/01 20:15:19 by mcarecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char *form_tested_path(t_token *token, char *path)
{
	char *tested_path;
	char *tested_path_tmp;

	tested_path = ft_strjoin(path, "/");
	tested_path_tmp = tested_path;
	tested_path = ft_strjoin(tested_path, token->cmd[0]);
	ft_freethis(&tested_path_tmp, NULL);
	return (tested_path);
}

/* Run a binary based on a relative path. */

static void run_path(t_shell *shell, t_token *token)
{
	int i;

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

static void run_sys_bin(t_shell *shell, t_token *token)
{
	char *tested_path;
	int i;

	i = 0;
	while (shell->paths[i])
	{
		tested_path = form_tested_path(token, shell->paths[i]);
		if (!access(tested_path, F_OK))
		{
			execve(tested_path, token->cmd, shell->envp);
			break;
		}
		ft_freethis(&tested_path, NULL);
		i++;
	}
	if (tested_path == NULL)
		command_not_found(shell, token->cmd[0]);
	ft_freethis(&tested_path, NULL);
}

void close_custom(int *fd)
{
	if (fd[0] != -1)
	{
		if (close(fd[0]) == -1)
			perror("close() failed");
		fd[0] = -1;
	}
}

void execute_token(t_shell *shell)
{
	t_token *token;
	int fd[2];
	int fd_original[2];
	pid_t pid;
	int fd_in = 0;
	int cmd_i;
	token = shell->h_token;
	cmd_i = 0;

	fd_original[0] = dup(STDIN_FILENO);
	fd_original[1] = dup(STDOUT_FILENO);
	int fd_file = -1;

	while (cmd_i < shell->h_token->n_cmds)
	{
		if (token->type == WORD)
		{
			t_token *tmp;

			tmp = token->next_token;
			while (tmp && tmp->type != PIPE)
			{
				if (tmp->type == REDIRECT && !ft_strncmp(tmp->value, ">", 2))
				{
					tmp = tmp->next_token;
					close_custom(&fd_file);
					fd_file = open(tmp->value, O_RDWR | O_CREAT | O_TRUNC, 0644);
					if (fd_file == -1)
					{
						perror("open() failed");
						exit(EXIT_FAILURE);
					}
					/* dup2(fd, STDOUT_FILENO);
					close(fd); */
				}
				else if (tmp->type == REDIRECT && !ft_strncmp(tmp->value, ">>", 3))
				{
					tmp = tmp->next_token;
					close_custom(&fd_file);
					fd_file = open(tmp->value, O_RDWR | O_CREAT | O_APPEND, 0644);
					if (fd_file == -1)
					{
						perror("open() failed");
						exit(EXIT_FAILURE);
					}
					/* dup2(fd, STDOUT_FILENO);
					close(fd); */
				}
				tmp = tmp->next_token;
			}

			/* func_pipe */
			pipe(fd);
			if (fd_in != 0)
			{
				if (dup2(fd_in, STDIN_FILENO) == -1)
				{
					printf("Deu bosta!\n");
				}
			}
			if (fd_file != -1)
			{
				dup2(fd_file, STDOUT_FILENO);
			}
			else if (token->next_token == NULL)
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
					wait(&shell->exit_status);
				}
			}
			if (fd_file != -1)
			{
				fd_in = fd_file;
				fd_file = -1;
			}
			else
			{
				if (fd_in != 0)
				{
					close_custom(&fd_in);
				}
				fd_in = fd[0];
				close_custom(&fd[1]);
			}
			cmd_i++;
		}
		else if (token->type == REDIRECT)
		{
			token = token->next_token;
		}
		token = token->next_token;
	}
	if (fd_in != 0)
		close_custom(&fd_in);
	close_custom(&fd_file);
	if (dup2(fd_original[0], STDIN_FILENO) == -1 || dup2(fd_original[1], STDOUT_FILENO) == -1)
	{
		printf("Deu bosta!\n");
	}
	close_custom(&fd_original[0]);
	close_custom(&fd_original[1]);
}
