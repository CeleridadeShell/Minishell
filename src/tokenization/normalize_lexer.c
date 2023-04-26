/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_lexer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarecho <mcarecho@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:06:16 by mcarecho          #+#    #+#             */
/*   Updated: 2023/04/22 19:39:104 by mcarecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#include <minishell.h>

char *when_quotes(t_shell *shell, t_token **tmp, char *input)
{
	char *value;

	value = NULL;
	value = ft_strchr(input + 1, *input);
	*tmp = append_token(shell, n_token(input, WORD, value - input + 1), *tmp);
	return (input + ft_strlen((*tmp)->value));
}

char *when_redirect(t_shell *shell, t_token **tmp, char *input)
{
	if (input[1] == *input)
		*tmp = append_token(shell, n_token(input, REDIRECT, 2), *tmp);
	else
	{
		*tmp = append_token(shell, n_token(input, REDIRECT, 1), *tmp);
	}
	return (input + ft_strlen((*tmp)->value));
}

char *when_sep_pipe(t_shell *shell, t_token **tmp, char *input, int holder)
{
	*tmp = append_token(shell, n_token(input, holder, 1), *tmp);
	input++;
	return (input);
}

char *when_word(t_shell *shell, t_token **tmp, char *input)
{
	*tmp = append_token(shell, get_next_token(input, 0), *tmp);
	return (input + ft_strlen((*tmp)->value));
}

void normalize(t_shell *shell, t_token *last_token)
{
	t_token *tmp;

	tmp = shell->h_token;
	shell->h_token = shell->h_token->next_token;
	shell->h_token->n_cmds = tmp->n_cmds;
	shell->h_token->n_tokens = tmp->n_tokens;
	free(tmp);
	if (shell->exit_status != 0)
		return (unexpected_token(shell, last_token->value));
	tmp = shell->h_token;
	while (tmp->next_token != NULL)
		tmp = tmp->next_token;
	if (tmp->type == REDIRECT || tmp->type == PIPE)
		throw_err(shell,"syntax error near unexpected token `newline'", 2);
}
