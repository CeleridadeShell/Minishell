/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarecho <mcarecho@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 19:47:28 by mcarecho          #+#    #+#             */
/*   Updated: 2023/04/22 19:35:058 by mcarecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <minishell.h>

void handle_token(t_shell *shell)
{
	char *input;

	start_tokens(shell);
	input = readline(shell->prompt); // Mudar como comando é lido
	add_history(input);
	//printf("%s\n", input);
	lexer(input, shell);
	parsing(shell->h_token, shell);
	if (!shell->exit_status)
		execute_token(shell);
	free_token(shell->h_token);
	free_paths(shell->paths);
}

int main(int argc, char **argv, const char **envp)
{
	t_shell shell;

	if (argv && argc > 1)
	{
		printf("Error: Too many arguments.\n");
		return (EXIT_FAILURE);
	}
	initialize_shell(&shell, envp);
	while (1)
	{
		shell.exit_status = 0;
		handle_signal();
		handle_token(&shell);
		shell.last_status = shell.exit_status;
	}
	printf("exit\n");
	free_shell(&shell);
	return (0);
}
