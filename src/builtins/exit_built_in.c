/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:57:33 by ccamargo          #+#    #+#             */
/*   Updated: 2023/05/14 18:52:32 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_n_numeric(char *n)
{
	int	i;

	i = 0;
	while (n[i])
	{
		if (ft_isdigit(n[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

void	ft_exit(t_token *token, t_shell *shell)
{
	printf("exit\n");
	if (token->cmd[1] && !is_n_numeric(token->cmd[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n", \
		token->cmd[1]);
		shell->exit_status = 2;
	}
	else if (count_number_of_params(token->cmd) > 2)
	{
		printf("minishell: exit: too many arguments\n");
		shell->exit_status = 1;
	}
	else if (token->cmd[1])
		shell->exit_status = ft_atoi(token->cmd[1]);
	free_token(token);
	free_paths(shell->paths);
	free_shell(shell);
	exit(shell->exit_status);
}
