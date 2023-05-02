/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:32:52 by ccamargo          #+#    #+#             */
/*   Updated: 2023/05/02 15:53:17 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	save_to_file(t_token *tmp, int *fd_file)
{
	tmp = tmp->next_token;
	close_custom(fd_file);
	*fd_file = open(tmp->value, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (*fd_file == -1)
	{
		perror("open() failed");
		exit(EXIT_FAILURE);
	}
}

static void	append_to_file(t_token *tmp, int *fd_file)
{
	tmp = tmp->next_token;
	close_custom(fd_file);
	*fd_file = open(tmp->value, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (*fd_file == -1)
	{
		perror("open() failed");
		exit(EXIT_FAILURE);
	}
}

void	redirect_outfile(t_tk_exec *exec_vars)
{
	t_token	*tmp;

	tmp = exec_vars->token->next_token;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == REDIRECT && !ft_strncmp(tmp->value, ">", 2))
		{
			save_to_file(tmp, &exec_vars->fd_file);
		}
		else if (tmp->type == REDIRECT && !ft_strncmp(tmp->value, ">>", 3))
		{
			append_to_file(tmp, &exec_vars->fd_file);
		}
		tmp = tmp->next_token;
	}
}
