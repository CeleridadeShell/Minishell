/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarecho <mcarecho@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 19:58:11 by mcarecho          #+#    #+#             */
/*   Updated: 2023/04/20 20:05:52 by mcarecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_strdup_char(char c)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * 2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

t_token	*parsing(t_token *token, t_global *g)
{
	t_token		*temp;
	t_type_t	last_type;
	int			index;

	index = 0;
	temp = token;
	last_type = SEPARATOR;
	while (index < token->n_cmds)
	{
		if (temp->type == WORD && last_type != REDIRECT)
		{
			temp->cmd = ft_split_pipex(temp->value, g);
			index++;
		}
		last_type = temp->type;
		temp = temp->next_token;
	}
	free(temp);
	return (token);
}
