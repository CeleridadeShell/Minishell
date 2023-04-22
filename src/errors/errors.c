/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarecho <mcarecho@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:11:33 by mcarecho          #+#    #+#             */
/*   Updated: 2023/04/22 19:14:48 by mcarecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
*@brief Checks the string for quotes
*@param argument the string to be checked
*@return -1 if not closed, 0 if closed.
*/
int	check_quotes(char *argument)
{
	int		index;
	char	quote;

	index = 0;
	while (argument[index])
	{
		if (argument[index] == '\'' || argument[index] == '\"')
		{
			quote = argument[index];
			while (argument[index] && argument[index] != quote)
				index++;
			if (argument[index] != quote)
			{
				ft_putendl_fd("Error: Unmatched quotes.", 2);
				return (-1);
			}
		}
		index++;
	}
	return (0);
}

/**
*@brief Checks input is empty
*@param input the input sent after the prompt
*@return -1 if only spaces, 0 if others.
*/
int	is_empty(char *input)
{
	int	index;
	int	space;

	index = 0;
	space = 0;
	while (input[index] != '\0')
	{
		if (is_whitespace(input[index]))
			space++;
		index++;
	}
	if (space == index)
		return (-1);
	return (0);
}

/**
*@brief Checks input (for errors)
*@param input the input sent after the prompt
*@return False if no errors, True if errors.
*/
int	check_input(char *input)
{
	int	check;

	check = FALSE;
	if (!input || ft_strlen(input) == 0)
		check = TRUE;
	else if (is_empty(input))
		check = TRUE;
	else if (check_quotes(input))
		check = TRUE;
	return (check);
}

void	error_handler(t_shell *shell)
{
	t_token	*tmp;
	char	*error;

	tmp = shell->h_token;
	while (tmp)
	{
		error = tmp->value;
		if (tmp->next_token == NULL)
			break ;
		free(tmp->value);
		tmp = tmp->next_token;
	}
	printf("minishell: syntax error near unexpected token `%s'\n", error);
	free(error);
	shell->h_token = NULL;
}
