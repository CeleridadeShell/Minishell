/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:03:06 by ccamargo          #+#    #+#             */
/*   Updated: 2023/05/05 20:20:51 by ccamargo         ###   ########.fr       */
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

void	throw_err_cd(t_shell *shell, char *err, int status)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(err, 2);
	ft_putstr_fd(": No such file or directory", 2);
	ft_putchar_fd('\n', 2);
	shell->exit_status = status;
}
