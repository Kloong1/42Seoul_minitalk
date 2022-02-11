/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <yohkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 20:06:17 by yohkim            #+#    #+#             */
/*   Updated: 2021/07/08 15:23:13 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	ft_putnbr_fd_rec(long n, int fd)
{
	char	digit;

	digit = n % 10 + '0';
	if (n / 10 == 0)
	{
		write(fd, &digit, 1);
		return ;
	}
	ft_putnbr_fd_rec(n / 10, fd);
	write(fd, &digit, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	num;

	if (fd < 0)
		return ;
	num = n;
	if (num < 0)
	{
		write(fd, "-", 1);
		num = -num;
	}
	ft_putnbr_fd_rec(num, fd);
}
