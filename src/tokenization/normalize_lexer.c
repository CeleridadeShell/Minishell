/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_lexer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarecho <mcarecho@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:06:16 by mcarecho          #+#    #+#             */
/*   Updated: 2023/04/20 21:14:02 by mcarecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#include <minishell.h>

char	*when_quotes(t_global *g, t_token **tmp, char *input)
{
	char	*value;

	value = NULL;
	value = ft_strchr(input + 1, *input);
	*tmp = append_token(g, n_token(input, WORD, value - input + 1),*tmp);
	return (input + ft_strlen((*tmp)->value));
}

char	*when_redirect(t_global *g, t_token **tmp, char *input)
{
	if (input[1] == *input)
		*tmp = append_token(g, n_token(input, REDIRECT, 2), *tmp);
	else
	{
		*tmp = append_token(g, n_token(input, REDIRECT, 1), *tmp);
	}
	return (input + ft_strlen((*tmp)->value));
}

char	*when_sep_pipe(t_global *g, t_token **tmp, char *input, int holder)
{
	*tmp = append_token(g, n_token(input, holder, 1), *tmp);
	input++;
	return (input);
}

char	*when_word(t_global *g, t_token **tmp, char *input)
{
	*tmp = append_token(g, get_next_token(input, 0), *tmp);
	return (input + ft_strlen((*tmp)->value));
}

void	normalize(t_global *g)
{
	t_token	*tmp;

	tmp = g->h_token;
	g->h_token = g->h_token->next_token;
	g->h_token->n_cmds = tmp->n_cmds;
	g->h_token->n_tokens = tmp->n_tokens;
	free(tmp);
	if (g->exit_status != 0)
		return (error_handler(g));
	tmp = g->h_token;
	while (tmp->next_token != NULL)
		tmp = tmp->next_token;
	if (tmp->type == REDIRECT || tmp->type == PIPE)
	{
		g->exit_status = 2;
		free(tmp->value);
		tmp->value = ft_strdup("newline");
		return (error_handler(g));
	}
}

