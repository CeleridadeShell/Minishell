/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_infile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 20:01:48 by mcarecho          #+#    #+#             */
/*   Updated: 2023/05/13 17:42:02 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	open_infile(t_shell *shell, t_token *token, int *fd_file)
{
	t_token	*tmp;
	char	*tmp_str;

	tmp = token->next_token;
	close_custom(fd_file);
	*fd_file = open(tmp->value, O_RDONLY, 0644);
	if (*fd_file == -1)
	{
		tmp_str = ft_strjoin(tmp->value, ": No such file or directory");
		throw_err(shell, tmp_str, 1);
		ft_freethis(&tmp_str, NULL);
	}
}

static void	pid_0_while(t_tk_exec *exec_vars, t_shell *shell, t_token *tmp)
{
	char	*r;

	r = readline("> ");
	if (r == NULL)
	{
		close(exec_vars->fd_heredoc);
		exit(EXIT_FAILURE);
	}
	else if (!ft_strncmp(r, tmp->value, ft_strlen(tmp->value) + 1))
	{
		free(r);
		close(exec_vars->fd_heredoc);
		exit(EXIT_SUCCESS);
	}
	else if (ft_strlen(r) != 0)
	{
		cmd_expand_str(&r, shell);
		ft_putendl_fd(r, exec_vars->fd_heredoc);
		free(r);
	}
}

static void	heredoc_pid_0(t_tk_exec *exec_vars, t_shell *shell, t_token *tmp)
{
	handle_signal_heredoc();
	unlink(".tmp");
	exec_vars->fd_heredoc = open(".tmp", O_RDWR | O_CREAT, 0777);
	dup2(exec_vars->fd_original[0], STDIN_FILENO);
	dup2(exec_vars->fd_original[1], STDOUT_FILENO);
	while (1)
		pid_0_while(exec_vars, shell, tmp);
	close(exec_vars->fd_heredoc);
	exit(EXIT_SUCCESS);
}

static void	heredoc(t_token *token, t_tk_exec *exec_vars, t_shell *shell)
{
	pid_t	pid;
	t_token	*tmp;

	fix_sigint_exec();
	tmp = token->next_token;
	pid = fork();
	if (pid == -1)
	{
		perror("fork() failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		heredoc_pid_0(exec_vars, shell, tmp);
	else
	{
		wait(NULL);
		close_custom(&exec_vars->fd_heredoc);
		exec_vars->fd_heredoc = open(".tmp", O_RDWR | O_CREAT, 0777);
		exec_vars->fd_in = exec_vars->fd_heredoc;
	}
}

void	redirect_infile(t_tk_exec *exec_vars, t_shell *shell)
{
	t_token	*tmp;

	tmp = exec_vars->token;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == REDIRECT && !ft_strncmp(tmp->value, "<", 2))
		{
			open_infile(shell, tmp, &exec_vars->fd_in);
		}
		else if (tmp->type == REDIRECT && !ft_strncmp(tmp->value, "<<", 3))
		{
			heredoc(tmp, exec_vars, shell);
		}
		tmp = tmp->next_token;
	}
}
