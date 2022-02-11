/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <yohkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 15:46:16 by yohkim            #+#    #+#             */
/*   Updated: 2021/07/08 15:21:39 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned int	i;
	unsigned char	*dst_uc;
	unsigned char	*src_uc;

	if (dst > src)
	{
		i = 0;
		dst_uc = (unsigned char *)dst;
		src_uc = (unsigned char *)src;
		while (i < len)
		{
			dst_uc[len - i - 1] = src_uc[len - i - 1];
			i++;
		}
	}
	else if (dst < src)
		ft_memcpy(dst, src, len);
	return (dst);
}
