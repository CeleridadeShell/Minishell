/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarecho <mcarecho@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:17:44 by ccamargo          #+#    #+#             */
/*   Updated: 2023/05/03 21:15:31 by mcarecho         ###   ########.fr       */
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

	init_exec_vars(&exec_vars, shell);
	while (exec_vars.cmd_i < shell->h_token->n_cmds)
	{
		if (exec_vars.token->type == WORD)
		{
			redirect_outfile(&exec_vars);
			redirect_infile(&exec_vars, shell);
			pipe(exec_vars.fd);
			set_io_redirection(&exec_vars, shell->h_token->n_cmds);
			run_command(&exec_vars, shell);
			set_fd_variables(&exec_vars);
			exec_vars.cmd_i++;
		}
		else if (exec_vars.token->type == REDIRECT)
			exec_vars.token = exec_vars.token->next_token;
		exec_vars.token = exec_vars.token->next_token;
	}
	if (exec_vars.fd_in != 0)
		close_custom(&exec_vars.fd_in);
	close_custom(&exec_vars.fd_file);
	dup2(exec_vars.fd_original[0], STDIN_FILENO);
	dup2(exec_vars.fd_original[1], STDOUT_FILENO);
	close_custom(&exec_vars.fd_original[0]);
	close_custom(&exec_vars.fd_original[1]);
}
