/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_var_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 17:55:58 by ccamargo          #+#    #+#             */
/*   Updated: 2023/05/03 19:15:06 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	replace_cmd_typed(t_token *token, char *found_var, int i, int j)
{
	char	*str_part1;
	char	*str_part2;
	char	*tmp_cmd_typed;

	str_part1 = ft_substr(token->value, 0, i);
	str_part2 = ft_substr(token->value, i + j + 1, ft_strlen(token->value));
	tmp_cmd_typed = ft_strjoin(str_part1, found_var);
	ft_freethis(&token->value, NULL);
	token->value = ft_strjoin(tmp_cmd_typed, str_part2);
	ft_freethis(&tmp_cmd_typed, NULL);
	ft_freethis(&str_part1, NULL);
	ft_freethis(&str_part2, NULL);
}

static void	search_env_vars(t_shell *shell, t_token *token, int i)
{
	char	*env_var;
	char	*found_var;
	int		j;

	j = 0;
	found_var = NULL;
	env_var = ft_strchr(&token->value[i + 1], ' ');
	if (env_var == NULL)
		j = ft_strlen(token->value) - i - 1;
	else
		j += env_var - &token->value[i + 1];
	found_var = ft_substr(token->value, i + 1, j);
	env_var = ft_strtrim(found_var, "\"");
	j = ft_strlen(env_var);
	ft_freethis(&found_var, NULL);
	found_var = find_envp_field(shell, env_var);
	if (found_var == NULL)
	{
		if (ft_strncmp(env_var, "?", 1) == 0)
			found_var = ft_itoa(shell->last_status);
		else
			found_var = ft_strdup("");
	}
	replace_cmd_typed(token, found_var, i, j);
	ft_freethis(&found_var, NULL);
}

static void	remove_dollar_sign(t_token *token, int i)
{
	char	*str_part1;
	char	*str_part2;

	while (token->value[i])
	{
		if (token->value[i] == '$')
		{
			str_part1 = ft_substr(token->value, 0, i);
			str_part2 = ft_substr(token->value, i + 1, ft_strlen(token->value));
			ft_freethis(&token->value, NULL);
			token->value = ft_strjoin(str_part1, str_part2);
		}
		i++;
	}
}

static void	found_dollar_sign(t_shell *shell, t_token *token, int i, char quote)
{
	if ((token->value[i + 1] == '\'' || token->value[i + 1] == '\"'))
	{
		if (token->value[i + 1] == '\'' && quote == '\0')
			remove_dollar_sign(token, i);
		else if (token->value[i + 1] == '\"' && quote == '\0')
			remove_quotes(token, i);
		else if (token->value[i + 1] == '\"' && quote == '\"')
			return ;
	}
	else
		search_env_vars(shell, token, i);
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
			found_dollar_sign(shell, token, i, quote);
		i++;
	}
}
