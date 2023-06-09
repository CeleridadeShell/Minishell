/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 21:41:45 by ccamargo          #+#    #+#             */
/*   Updated: 2023/05/04 17:26:14 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* Find enviroment variables in the struct s_shell. */

char	*find_envp_field(t_shell *shell, const char *field)
{
	int		i;
	char	*field_tested;

	i = 0;
	if (!shell || !field)
		return (NULL);
	while (shell->envp[i])
	{
		field_tested = ft_substr(shell->envp[i], 0, ft_strchr(shell->envp[i], \
		'=') - shell->envp[i]);
		if (!ft_strncmp(field_tested, field, ft_strlen(field_tested)))
		{
			ft_freethis(&field_tested, NULL);
			return (ft_substr(shell->envp[i], ft_strchr(shell->envp[i], '=') \
			- shell->envp[i] + 1, ft_strlen(shell->envp[i])));
		}
		ft_freethis(&field_tested, NULL);
		i++;
	}
	return (NULL);
}

int	find_envp_field_index(t_shell *shell, const char *field)
{
	int		i;
	char	*field_tested;

	i = 0;
	if (!shell || !field)
		return (-1);
	while (shell->envp[i])
	{
		field_tested = ft_substr(shell->envp[i], 0, ft_strchr(shell->envp[i], \
		'=') - shell->envp[i]);
		if (!ft_strncmp(field_tested, field, ft_strlen(field_tested)))
		{
			ft_freethis(&field_tested, NULL);
			return (i);
		}
		ft_freethis(&field_tested, NULL);
		i++;
	}
	return (-1);
}

void	replace_env_field(t_shell *shell, const char *field, \
const char *new_field)
{
	int	i;

	i = find_envp_field_index(shell, field);
	ft_freethis(&shell->envp[i], NULL);
	shell->envp[i] = ft_strdup(new_field);
}

void	remove_quotes(char **str, int i)
{
	char	*temp;
	char	*temp2;
	char	*temp3;
	int		second_quote;

	second_quote = ft_strchr(&str[0][i + 2], '"') - &str[0][i + 2];
	temp = ft_substr(str[0], 0, i + 1);
	temp2 = ft_substr(str[0], i + 2, second_quote);
	temp3 = ft_strjoin(temp, temp2);
	ft_freethis(&temp, NULL);
	ft_freethis(&temp2, NULL);
	temp = ft_substr(str[0], i + second_quote + 3, ft_strlen(str[0]));
	ft_freethis(&str[0], NULL);
	str[0] = ft_strjoin(temp3, temp);
	ft_freethis(&temp, NULL);
}
