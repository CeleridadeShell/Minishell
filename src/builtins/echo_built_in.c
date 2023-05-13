/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:56:31 by ccamargo          #+#    #+#             */
/*   Updated: 2023/05/13 16:41:04 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_echo(t_token *token)
{
	int		new_line;
	int		i;

	new_line = 1;
	i = 1;
	if (token->cmd[1])
	{
		if (!ft_strncmp((char *) token->cmd[1], "-n", ft_strlen((char *) \
		token->cmd[1])))
		{
			new_line = 0;
			i = 2;
		}
	}
	while (token->cmd[i])
	{
		printf("%s", token->cmd[i]);
		if (token->cmd[i + 1])
			printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
}
