/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_var_expansion_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:29:18 by ccamargo          #+#    #+#             */
/*   Updated: 2023/05/04 17:29:26 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	cmd_expand_str(char *str, t_shell *shell)
{
	int		i;
	char	quote;

	i = 0;
	quote = '\0';
	while (str[i])
	{
		if (str[i] == '\'' && (quote == '\0' || quote == '\''))
		{
			if (quote == '\'')
				quote = '\0';
			else
				quote = '\'';
		}
		else if (str[i] == '\"' && (quote == '\0' || quote == '\"'))
		{
			if (quote == '\"')
				quote = '\0';
			else
				quote = '\"';
		}
		else if (str[i] == '$' && quote != '\'')
			found_dollar_sign(shell, &str, i, quote);
		i++;
	}
}
