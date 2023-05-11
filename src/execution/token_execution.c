/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:17:44 by ccamargo          #+#    #+#             */
/*   Updated: 2023/05/11 20:44:53 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	close_custom(int *fd)
{
	if (fd[0] != -1)
	{
		if (close(fd[0]) == -1)
			perror("close() failed");
		fd[0] = -1;
	}
}

void	execute_token(t_shell *shell)
{
	t_tk_exec	exec_vars;
	t_token		*tmp_token;

	init_exec_vars(&exec_vars, shell);
	while (exec_vars.cmd_i < shell->h_token->n_cmds)
	{
		if (exec_vars.token->type == WORD)
		{
			if (exec_vars.cmd_i == 0)
			{
				tmp_token = exec_vars.token;
				exec_vars.token = shell->h_token;
			}
			redirect_outfile(&exec_vars);
			redirect_infile(&exec_vars, shell);
			if (exec_vars.cmd_i == 0)
			{
				exec_vars.token = tmp_token;
			}
			pipe(exec_vars.fd);
			set_io_redirection(&exec_vars, shell->h_token->n_cmds);
			if (shell->exit_status == 0)
				run_command(&exec_vars, shell);
			set_fd_variables(&exec_vars);
			exec_vars.cmd_i++;
		}
		else if (exec_vars.token->type == REDIRECT)
			exec_vars.token = exec_vars.token->next_token;
		exec_vars.token = exec_vars.token->next_token;
	}
	if (shell->h_token->n_cmds == 0)
	{
		redirect_outfile(&exec_vars);
		redirect_infile(&exec_vars, shell);
	}
	if (exec_vars.fd_in != 0)
		close_custom(&exec_vars.fd_in);
	close_custom(&exec_vars.fd_file);
	dup2(exec_vars.fd_original[0], STDIN_FILENO);
	dup2(exec_vars.fd_original[1], STDOUT_FILENO);
	close_custom(&exec_vars.fd_original[0]);
	close_custom(&exec_vars.fd_original[1]);
}
