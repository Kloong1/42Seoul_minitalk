/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <yohkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:48:32 by yohkim            #+#    #+#             */
/*   Updated: 2021/07/08 15:35:44 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str_mapped;
	size_t			len;
	unsigned int	i;

	if (!s || !f)
		return (0);
	len = ft_strlen(s);
	str_mapped = malloc(sizeof(char) * (len + 1));
	if (!str_mapped)
		return (0);
	i = 0;
	while (i < len)
	{
		str_mapped[i] = f(i, s[i]);
		i++;
	}
	str_mapped[len] = 0;
	return (str_mapped);
}
