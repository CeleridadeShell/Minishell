/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 19:58:08 by mcarecho          #+#    #+#             */
/*   Updated: 2023/05/13 00:10:23 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 *@brief adds a new token to a linked list of tokens.
 *@param tokens is a pointer to a t_token pointer. It is used to keep track of
 *the linked list of tokens.
 *@param token is a pointer to a t_token representing a new token to be added
 *to the linked list.
 *@return none.
 */
t_token	*append_token(t_shell *shell, t_token *token, t_token *last_token)
{
	t_token	*current;

	current = shell->h_token;
	while (current->next_token != NULL)
		current = current->next_token;
	current->next_token = token;
	if (token->type == WORD && last_token->type != REDIRECT)
		shell->h_token->n_cmds++;
	shell->exit_status = verify_unexpecte_token(token, last_token);
	shell->h_token->n_tokens++;
	return (token);
}

/**
 *@brief gets a pointer to an "input" character pointer.
 *@param input
 *@return It returns a new character pointer containing the substring from the
 *beginning of the "input" string to the first separator or white space character
 */
char	*get_value(char **input)
{
	char	*value;
	int		len;

	len = 0;
	while ((*input)[len] && !is_separator((*input)[len]) && \
	!is_pipe((*input[len])) && !is_redirect((*input)[len]))
		len++;
	if (is_whitespace((*input)[len]))
		len++;
	value = malloc(sizeof(char) * (len + 1));
	if (!value)
		return (NULL);
	ft_strlcpy(value, *input, len + 1);
	*input += len;
	return (value);
}

int	is_symbol(char c)
{
/* 	if (is_separator(c))
		return (SEPARATOR); */
	if (is_redirect(c))
		return (REDIRECT);
	else if (is_pipe(c))
		return (PIPE);
	else if (is_quote(c))
		return (QUOTE);
	else if (is_whitespace(c))
		return (WHITESPACE);
	else
		return (WORD);
}

/**
 *@brief This function is responsible for parsing an input string and creating a
 *linked list of tokens, where each token is represented by a t_token object.
 *@param input
 *@return returns a pointer to an object of type t_token
 */
void	lexer(char *input, t_shell *shell)
{
	t_token	*tmp;
	int		holder;

	tmp = shell->h_token;
	holder = is_symbol(*input);
	while (*input)
	{
		if (shell->exit_status != 0)
			return (unexpected_token(shell, tmp->value));
		holder = is_symbol(*input);
		if (holder == WHITESPACE)
			input++;
		else if (holder == SEPARATOR || holder == PIPE)
			input = when_sep_pipe(shell, &tmp, input, holder);
		else if (holder == REDIRECT)
			input = when_redirect(shell, &tmp, input);
		else
			input = when_word(shell, &tmp, input);
	}
	normalize(shell, tmp);
}
