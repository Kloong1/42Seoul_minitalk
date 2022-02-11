/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <yohkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 14:34:57 by yohkim            #+#    #+#             */
/*   Updated: 2021/07/08 15:29:59 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t			total_len;
	unsigned int	i;

	i = 0;
	while (i < dstsize && dst[i])
		i++;
	total_len = ft_strlen(src) + i;
	while (i < dstsize)
	{
		if (*src == '\0' || i + 1 == dstsize)
		{
			dst[i] = '\0';
			break ;
		}
		dst[i] = *src;
		i++;
		src++;
	}
	return (total_len);
}
