/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarecho <mcarecho@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 21:41:45 by ccamargo          #+#    #+#             */
/*   Updated: 2023/04/22 17:36:46 by mcarecho         ###   ########.fr       */
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

void	replace_env_field(t_shell *shell, const char *field, const char \
*new_field)
{
	int	i;

	i = find_envp_field_index(shell, field);
	ft_freethis(&shell->envp[i], NULL);
	shell->envp[i] = ft_strdup(new_field);
}
