/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarecho <mcarecho@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 21:37:04 by ccamargo          #+#    #+#             */
/*   Updated: 2023/04/20 20:44:22 by mcarecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* readline() function causes leaks on its own. */
/* Free all memory allocated for the shell struct. */

void	free_shell(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
	{
		ft_freethis(&(*shell).envp[i], NULL);
		i++;
	}
	free(shell->envp);
	shell->envp = NULL;
	ft_freethis(&(*shell).prompt, NULL);
	rl_clear_history();
}


/* Free all memory allocated for the cmd struct. */

void	free_cmd(t_cmd *cmd)
{
	t_list	*tmp;
	int		i;

	tmp = cmd->cmd_table;
	while (tmp)
	{
		ft_lstclear((t_list **) &tmp->content, free);
		tmp = tmp->next;
	}
	ft_lstclear(&(*cmd).cmd_table, free);
	ft_freethis(&(*cmd).cmd_typed, NULL);
	i = 0;
	while (cmd->paths[i])
	{
		ft_freethis(&cmd->paths[i], NULL);
		i++;
	}
	free(cmd->paths);
	cmd->paths = NULL;
}
