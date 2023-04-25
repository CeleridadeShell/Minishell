/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 23:53:45 by ccamargo          #+#    #+#             */
/*   Updated: 2022/08/25 22:33:55 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_putnbr_fd(int n, int fd)
{
	long	x;

	x = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		x = (x * (-1));
	}
	if (x >= 10)
		ft_putnbr_fd((x / 10), fd);
	ft_putchar_fd(((x % 10) + 48), fd);
}
