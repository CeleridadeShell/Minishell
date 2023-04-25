/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:33:00 by ccamargo          #+#    #+#             */
/*   Updated: 2022/08/25 22:32:57 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*sp;
	size_t			i;

	sp = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (sp[i] == (unsigned char) c)
			return (&sp[i]);
		i++;
	}
	return (NULL);
}
