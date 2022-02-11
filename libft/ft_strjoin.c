/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <yohkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 13:25:47 by yohkim            #+#    #+#             */
/*   Updated: 2021/07/06 17:58:17 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str_joined;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str_joined = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!str_joined)
		return (0);
	ft_memcpy(str_joined, s1, s1_len);
	ft_strlcpy(str_joined + s1_len, s2, s2_len + 1);
	return (str_joined);
}
