/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarecho <mcarecho@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 21:37:04 by ccamargo          #+#    #+#             */
/*   Updated: 2023/04/24 19:21:43 by mcarecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* readline() function causes leaks on its own. */
/* Free all memory allocated for the shell struct. */

void	free_shell(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
	{
		ft_freethis(&(*shell).envp[i], NULL);
		i++;
	}
	free(shell->envp);
	shell->envp = NULL;
	ft_freethis(&(*shell).prompt, NULL);
	rl_clear_history();
}


/* Free all memory allocated for the cmd struct. */

void	free_token(t_token *token)
{
	int		i;
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		ft_freethis(&(token)->value, NULL);
		i = 0;
		while (token->cmd[i])
		{
			ft_freethis(&token->cmd[i], NULL);
			i++;
		}
		free(token->cmd);
		token->cmd = NULL;
		i = 0;
		while (token->paths != NULL && token->paths[i])
		{
			ft_freethis(&token->paths[i], NULL);
			i++;
		}
		ft_freethis((char **)&token->paths, NULL);
		token = token->next_token;
		free(tmp);
		tmp = NULL;
	}
	token = NULL;
}
