/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 10:52:25 by ccamargo          #+#    #+#             */
/*   Updated: 2022/08/25 22:33:09 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*sptr;
	size_t			i;

	sptr = s;
	i = 0;
	while (i < n)
	{
		sptr[i] = (unsigned char) c;
		i++;
	}
	return (s);
}
