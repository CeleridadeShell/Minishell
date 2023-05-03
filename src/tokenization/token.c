/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:10:07 by mcarecho          #+#    #+#             */
/*   Updated: 2023/05/03 19:12:57 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
*@brief cover the input string from position pos until it finds a separator
*(whitespace, redirection or pipe), and creates and returns the respective token
*with the function corresponding to the separation rules
*@param input
*@param pos
*@return the next token found in the string
*/
t_token	*get_next_token(char *input, int end_pos)
{
	while (input[end_pos] != '\0')
	{
		if (is_quote(input[end_pos]))
		{
			end_pos += ft_strchr(&input[end_pos] + 1, input[end_pos])
				- &input [end_pos];
		}
		else if (is_redirect(input[end_pos]) || is_pipe(input[end_pos])
			|| is_separator(input[end_pos]))
		{
			return (n_token(input, WORD, end_pos - 1));
		}
		end_pos++;
	}
	return (n_token(input, WORD, end_pos));
}

/**
*@brief a new token with the type and value specified in the parameters
*@param value
*@param type
*@return takes a value and a type and creates a new token with those values,
*setting the start and end positions to 0 and the next token to NULL
*/
t_token	*n_token(char *value, int type, int size)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->n_cmds = 0;
	token->n_tokens = 0;
	token->type = type;
	token->value = ft_substr(value, 0, size);
	token->next_token = NULL;
	token->cmd = NULL;
	return (token);
}

int	verify_unexpecte_token(t_token *current_token, t_token *last_token)
{
	if (current_token->type == PIPE && last_token->type == SEPARATOR)
		return (2);
	else if (current_token->type == PIPE && last_token->type == PIPE)
		return (2);
	else if (current_token->type == REDIRECT && last_token->type == REDIRECT)
		return (2);
	else if (current_token->type == PIPE && last_token->type == REDIRECT)
		return (2);
	else if (current_token->type == SEPARATOR && last_token->type == REDIRECT)
		return (2);
	else if (current_token->type == SEPARATOR && last_token->type == PIPE)
		return (2);
	else if (current_token->type == SEPARATOR && last_token->type == SEPARATOR)
		return (2);
	else
		return (0);
}
