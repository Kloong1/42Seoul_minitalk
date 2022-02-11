/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <yohkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 18:18:11 by yohkim            #+#    #+#             */
/*   Updated: 2021/07/08 15:27:26 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static const char	*ft_next_substr(char const *s, char c, size_t *len)
{
	char	*end_of_str;

	while (*s)
	{
		if (*s != c)
			break ;
		s++;
	}
	if (*s == 0)
		return (0);
	end_of_str = ft_strchr(s, c);
	if (!end_of_str)
		*len = ft_strlen(s);
	else
		*len = end_of_str - s;
	return (s);
}

static int	ft_count_substr(char const *s, char c)
{
	int		cnt;
	size_t	len;

	cnt = 0;
	len = 0;
	while (1)
	{
		s = ft_next_substr(s, c, &len);
		if (!s)
			break ;
		cnt++;
		s += len;
	}
	return (cnt);
}

static void	ft_free_substr_arr(char **substr_arr, int i)
{
	while (--i >= 0)
		free(substr_arr[i]);
	free(substr_arr);
}

static char	**ft_get_substr_arr(char const *s, char c, int cnt)
{
	char	**substr_arr;
	int		i;
	size_t	len;

	substr_arr = malloc(sizeof(char *) * (cnt + 1));
	if (!substr_arr)
		return (0);
	i = 0;
	len = 0;
	while (i < cnt)
	{
		s = ft_next_substr(s, c, &len);
		substr_arr[i] = ft_substr(s, 0, len);
		if (!substr_arr[i])
		{
			ft_free_substr_arr(substr_arr, i);
			return (0);
		}
		s += len;
		i++;
	}
	substr_arr[cnt] = 0;
	return (substr_arr);
}

char	**ft_split(char const *s, char c)
{
	if (!s)
		return (0);
	return (ft_get_substr_arr(s, c, ft_count_substr(s, c)));
}
