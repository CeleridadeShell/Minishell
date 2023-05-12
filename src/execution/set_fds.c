/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:16:09 by ccamargo          #+#    #+#             */
/*   Updated: 2023/05/12 19:34:42 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_exec_vars(t_tk_exec *exec_vars, t_shell *shell)
{
	exec_vars->pids = malloc((shell->h_token->n_cmds) * sizeof(pid_t));
	exec_vars->token = shell->h_token;
	exec_vars->fd_in = 0;
	exec_vars->cmd_i = 0;
	exec_vars->fd_original[0] = dup(STDIN_FILENO);
	exec_vars->fd_original[1] = dup(STDOUT_FILENO);
	exec_vars->fd_file = -1;
	exec_vars->fd_heredoc = -1;
}

void	set_io_redirection(t_tk_exec *exec_vars, int cmd_n)
{
	if (exec_vars->fd_in != 0)
		dup2(exec_vars->fd_in, STDIN_FILENO);
	if (exec_vars->fd_file != -1)
		dup2(exec_vars->fd_file, STDOUT_FILENO);
	else if (cmd_n == exec_vars->cmd_i + 1)
		dup2(exec_vars->fd_original[1], STDOUT_FILENO);
	else
		dup2(exec_vars->fd[1], STDOUT_FILENO);
}

void	set_fd_variables(t_tk_exec *exec_vars)
{
	if (exec_vars->fd_in == exec_vars->fd_heredoc && exec_vars->fd_in != -1)
	{
		if (unlink(".tmp") != 0)
			perror("unlink() failed");
		exec_vars->fd_heredoc = -1;
	}
	if (exec_vars->fd_file != -1)
	{
		exec_vars->fd_in = exec_vars->fd_file;
		exec_vars->fd_file = -1;
	}
	else
	{
		if (exec_vars->fd_in != 0)
		{
			close_custom(&exec_vars->fd_in);
		}
		exec_vars->fd_in = exec_vars->fd[0];
		close_custom(&exec_vars->fd[1]);
	}
}
