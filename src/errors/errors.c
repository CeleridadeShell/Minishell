/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarecho <mcarecho@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:11:33 by mcarecho          #+#    #+#             */
/*   Updated: 2023/04/26 18:34:14 by mcarecho         ###   ########.fr       */
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

void	unexpected_token(t_shell *shell, char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	shell->exit_status = 2;
}

void	throw_err(t_shell *shell, char *err, int status)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(err, 2);
	ft_putchar_fd('\n', 2);
	shell->exit_status = status;
}

void 	command_not_found(t_shell *shell, char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	shell->exit_status = 127;
}
