/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <yohkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 15:18:18 by yohkim            #+#    #+#             */
/*   Updated: 2021/07/06 17:49:01 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_get_len(long num)
{
	size_t	len;

	len = 0;
	if (num == 0)
		return (1);
	while (num)
	{
		num /= 10;
		len++;
	}
	return (len);
}

static char	*ft_get_num_str(long num, size_t len)
{
	char	*str;

	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	str[len] = 0;
	str[0] = '-';
	if (num == 0)
	{
		str[0] = '0';
		return (str);
	}
	while (num)
	{
		str[--len] = num % 10 + '0';
		num /= 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	long	num;
	size_t	len;

	num = n;
	len = 0;
	if (num < 0)
	{
		num = -num;
		len++;
	}
	len += ft_get_len(num);
	return (ft_get_num_str(num, len));
}
