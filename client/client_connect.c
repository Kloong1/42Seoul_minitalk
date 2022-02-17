/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_connect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <42.4.yohkim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 13:57:50 by yohkim            #+#    #+#             */
/*   Updated: 2022/02/18 00:25:34 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_conn_stat	g_conn_stat;

int	connect(void)
{
	int	try_cnt;

	try_cnt = 0;
	while (try_cnt < 3)
	{
		kill(g_conn_stat.server_pid, SIGUSR1);
		if (sleep(10) != 0 || g_conn_stat.response == SIGUSR1)
			break ;
		try_cnt++;
	}
	if (try_cnt == 3)
		return (-1);
	return (0);
}

void	handler_connect(int signo)
{
	g_conn_stat.response = signo;
	g_conn_stat.bitidx = 31;
	signal(SIGUSR1, handler_msglen);
	signal(SIGUSR2, handler_msglen);
}

void	handler_wait_queue(int signo)
{
	(void)signo;
	pause();
}
