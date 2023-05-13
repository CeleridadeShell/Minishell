/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_var_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 17:55:58 by ccamargo          #+#    #+#             */
/*   Updated: 2023/05/13 16:50:59 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	replace_cmd_typed(char **str, char *found_var, int i, int j)
{
	char	*str_part1;
	char	*str_part2;
	char	*tmp_cmd_typed;

	str_part1 = ft_substr(str[0], 0, i);
	str_part2 = ft_substr(str[0], i + j + 1, ft_strlen(str[0]));
	tmp_cmd_typed = ft_strjoin(str_part1, found_var);
	ft_freethis(&str[0], NULL);
	str[0] = ft_strjoin(tmp_cmd_typed, str_part2);
	ft_freethis(&tmp_cmd_typed, NULL);
	ft_freethis(&str_part1, NULL);
	ft_freethis(&str_part2, NULL);
}

static void	remove_dollar_sign(char **str, int i)
{
	char	*str_part1;
	char	*str_part2;

	while (str[0][i])
	{
		if (str[0][i] == '$')
		{
			str_part1 = ft_substr(str[0], 0, i);
			str_part2 = ft_substr(str[0], i + 1, ft_strlen(str[0]));
			ft_freethis(str, NULL);
			str[0] = ft_strjoin(str_part1, str_part2);
		}
		i++;
	}
}

void	found_dollar_sign(t_shell *shell, char **str, int i, char quote)
{
	if ((str[0][i + 1] == '\'' || str[0][i + 1] == '\"'))
	{
		if (str[0][i + 1] == '\'' && quote == '\0')
			remove_dollar_sign(str, i);
		else if (str[0][i + 1] == '\"' && quote == '\0')
			remove_quotes(str, i);
		else if (str[0][i + 1] == '\"' && quote == '\"')
			return ;
	}
	else
		search_env_vars(str, shell, i);
}

void	cmd_expand_var(t_token *token, t_shell *shell)
{
	int		i;
	char	quote;

	i = 0;
	quote = '\0';
	while (token->value[i])
	{
		if (token->value[i] == '\'' && (quote == '\0' || quote == '\''))
		{
			if (quote == '\'')
				quote = '\0';
			else
				quote = '\'';
		}
		else if (token->value[i] == '\"' && (quote == '\0' || quote == '\"'))
		{
			if (quote == '\"')
				quote = '\0';
			else
				quote = '\"';
		}
		else if (token->value[i] == '$' && quote != '\'')
			found_dollar_sign(shell, &token->value, i, quote);
		i++;
	}
}
