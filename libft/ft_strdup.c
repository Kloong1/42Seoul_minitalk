/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <yohkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 17:14:42 by yohkim            #+#    #+#             */
/*   Updated: 2021/07/06 14:38:03 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*dst;
	size_t	src_len;

	src_len = ft_strlen(s1);
	dst = malloc(sizeof(char) * src_len + 1);
	if (!dst)
		return (0);
	ft_strlcpy(dst, s1, src_len + 1);
	return (dst);
}
