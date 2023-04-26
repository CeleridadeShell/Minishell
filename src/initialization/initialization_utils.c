/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarecho <mcarecho@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 21:39:05 by ccamargo          #+#    #+#             */
/*   Updated: 2023/04/26 18:11:07 by mcarecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* Initialize shell variables. */

void initialize_shell(t_shell *shell, const char **envp)
{
	int line_count;
	char *user;
	int i;

	line_count = 0;
	i = 0;
	while (envp[line_count])
		line_count++;
	shell->envp = (char **)ft_calloc(line_count + 1, sizeof(char *));
	while (line_count)
	{
		shell->envp[i] = ft_strdup(envp[i]);
		i++;
		line_count--;
	}
	replace_env_field(shell, "SHELL", "SHELL=minishell");
	user = find_envp_field(shell, "USER");
	shell->prompt = ft_strjoin(user, " > ");
	ft_freethis(&user, NULL);
	shell->exit_status = 0;
	shell->last_status = 0;
}

void start_tokens(t_shell *shell)
{
	char *env_path;

	shell->h_token = malloc(sizeof(t_token));
	shell->h_token->value = NULL;
	shell->h_token->n_cmds = 0;
	shell->h_token->n_tokens = 0;
	env_path = find_envp_field(shell, "PATH");
	shell->paths = ft_split(env_path, ':');
	ft_freethis(&env_path, NULL);
	shell->h_token->next_token = NULL;
	shell->h_token->type = SEPARATOR;
}
