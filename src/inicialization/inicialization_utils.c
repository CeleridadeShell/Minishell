/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inicialization_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarecho <mcarecho@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 21:39:05 by ccamargo          #+#    #+#             */
/*   Updated: 2023/04/20 21:05:04 by mcarecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* Initialize shell variables. */

void	initialize_shell(t_shell *shell, const char **envp)
{
	int		line_count;
	char	*user;
	int		i;

	line_count = 0;
	i = 0;
	while (envp[line_count])
		line_count++;
	shell->envp = (char **) ft_calloc(line_count + 1, sizeof(char *));
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


void	start_tokens(t_token **tokens, t_shell *shell)
{
	*tokens = malloc(sizeof(t_token));
	(*tokens)->value = NULL;
	(*tokens)->n_cmds = 0;
	(*tokens)->n_tokens = 0;
	env_path = find_envp_field(shell, "PATH");
	cmd->paths = ft_split(env_path, ':');
	ft_freethis(&env_path, NULL);
	(*tokens)->next_token = NULL;
	(*tokens)->type = SEPARATOR;
}
