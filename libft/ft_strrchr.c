/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <yohkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 17:43:07 by yohkim            #+#    #+#             */
/*   Updated: 2021/07/06 16:49:39 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	chr;
	char	*loc;

	chr = (char)c;
	loc = 0;
	while (*s)
	{
		if (*s == chr)
			loc = (char *)s;
		s++;
	}
	if (chr == '\0')
		return ((char *)s);
	else
		return (loc);
}
