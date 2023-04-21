/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarecho <mcarecho@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 19:47:28 by mcarecho          #+#    #+#             */
/*   Updated: 2023/04/20 22:27:14 by mcarecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <minishell.h>

void	handle_cmd(t_shell *shell)
{
	t_token	cmd;
	char *input;

	initialize_cmd(shell, &cmd);
	input = readline(shell->prompt); //Mudar como comando é lido
	add_history(input);
	if (!shell->exit_status)
		execute_cmd(shell, &cmd);
	free_cmd(&cmd);
}

int	main(int argc, char **argv, const char **envp)
{
	t_shell	shell;

	if (argv && argc > 1)
	{
		ft_printf("Error: Too many arguments.\n");
		return (EXIT_FAILURE);
	}
	initialize_shell(&shell, envp);
	while (!shell.exit_status)
	{
		handle_signals();
		handle_cmd(&shell);
	}
	printf("exit\n");
	free_shell(&shell);
	return (0);
}

