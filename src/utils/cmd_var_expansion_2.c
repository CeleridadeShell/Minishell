/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_var_expansion_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:29:18 by ccamargo          #+#    #+#             */
/*   Updated: 2023/05/21 17:52:24 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	cmd_expand_str(char **str, t_shell *shell)
{
	int		i;
	char	quote;

	i = 0;
	quote = '\0';
	while (str[0][i])
	{
		if (str[0][i] == '\'' && (quote == '\0' || quote == '\''))
		{
			if (quote == '\'')
				quote = '\0';
			else
				quote = '\'';
		}
		else if (str[0][i] == '\"' && (quote == '\0' || quote == '\"'))
		{
			if (quote == '\"')
				quote = '\0';
			else
				quote = '\"';
		}
		else if (str[0][i] == '$' && quote != '\'')
			found_dollar_sign(shell, str, i, quote);
		i++;
	}
}

static void	search_env_vars_3(t_shell *shell, char **found_var, char *env_var)
{
	if (*found_var == NULL)
	{
		if (ft_strncmp(env_var, "?", 1) == 0)
			*found_var = ft_itoa(shell->last_status);
		else
			*found_var = ft_strdup("");
	}
}

static int	search_env_vars_2(char **env_var, char **str, int *j, int i)
{
	while (INVALID_CHARS[*j] != '\0')
	{
		if (INVALID_CHARS[*j] != '\"')
		{
			*env_var = ft_strchr(&str[0][i + 1], INVALID_CHARS[*j]);
			if (*env_var != NULL)
				return (0);
		}
		(*j)++;
	}
	*j = ft_strlen(str[0]) - i - 1;
	return (1);
}

void	search_env_vars(char **str, t_shell *shell, int i)
{
	char	*env_var;
	char	*found_var;
	int		j;

	j = 0;
	found_var = NULL;
	env_var = ft_strchr(&str[0][i + 1], ' ');
	if (env_var == NULL)
	{
		if (str[0][i + 1] != '?' && \
		search_env_vars_2(&env_var, str, &j, i) == 0)
			return ;
		j = ft_strlen(str[0]) - i - 1;
	}
	else
		j += env_var - &str[0][i + 1];
	found_var = ft_substr(str[0], i + 1, j);
	env_var = ft_strtrim(found_var, "\"\'");
	j = ft_strlen(env_var);
	ft_freethis(&found_var, NULL);
	found_var = find_envp_field(shell, env_var);
	search_env_vars_3(shell, &found_var, env_var);
	ft_freethis(&env_var, NULL);
	replace_cmd_typed(str, found_var, i, j);
	ft_freethis(&found_var, NULL);
}
