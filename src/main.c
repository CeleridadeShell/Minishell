/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:36:18 by ccamargo          #+#    #+#             */
/*   Updated: 2023/05/12 21:40:36 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <minishell.h>

void	handle_token(t_shell *shell)
{
	char	*input;

	start_tokens(shell);
	input = readline(shell->prompt); // Mudar como comando é lido
	if (!input)
	{
		free_token(shell->h_token);
		free_paths(shell->paths);
		free_shell(shell);
		printf("exit\n");
		exit(0);
	}
	else if(*input != 0)
	{
		add_history(input);
		if (check_quotes(input) == 0)
		{
			lexer(input, shell);
			ft_freethis(&input, NULL);
			parsing(shell->h_token, shell);
			if (!shell->exit_status)
				execute_token(shell);
		}
		else
			ft_freethis(&input, NULL);
	}
	free_token(shell->h_token);
	free_paths(shell->paths);
}

int	main(int argc, char **argv, const char **envp)
{
	t_shell	shell;

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
