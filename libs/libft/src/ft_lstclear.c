/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 21:18:11 by ccamargo          #+#    #+#             */
/*   Updated: 2022/08/25 22:32:14 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*nxt;

	if (!lst || !del)
		return ;
	tmp = *lst;
	while (tmp)
	{
		nxt = tmp->next;
		ft_lstdelone(tmp, del);
		tmp = nxt;
	}
	*lst = NULL;
}
