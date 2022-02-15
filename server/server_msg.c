/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_msg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <42.4.yohkim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 20:14:44 by yohkim            #+#    #+#             */
/*   Updated: 2022/02/15 14:56:52 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

#include <stdio.h>

t_conn_stat g_conn_stat;

int recieve_msg()
{
	int bitidx;

	bitidx = 7;
	while (g_conn_stat.msgidx < g_conn_stat.msglen)
	{
		if (sleep(5) == 0)
		{
			free(g_conn_stat.msg);
			return (RESPONSE_NORESP);
		}
		if (g_conn_stat.client_sig == SIGUSR2)
			g_conn_stat.msg[g_conn_stat.msgidx] |= 1 << bitidx;
		bitidx--;
		if (bitidx < 0)
		{
			bitidx = 7;
			g_conn_stat.msgidx++;
		}
		kill(g_conn_stat.client_pid, SIGUSR1);
	}
	g_conn_stat.msg[g_conn_stat.msgidx] = '\0';

	printf("%s\n", g_conn_stat.msg);
	free(g_conn_stat.msg);

	return (RESPONSE_SUCCESS);
}

int recieve_msg_char()
{
	int try_cnt;
	int idx;
	int unslept_sec;

	try_cnt = 0;
	idx = 7;
	while (try_cnt < 3 && idx >= 0)
	{
		unslept_sec = sleep(3);
		if (unslept_sec == 0 && idx == 7)
			return (RESPONSE_NORESP);
		if (unslept_sec == 0 && idx < 7)
		{
			/* retry_recieve(&try_cnt, &idx, 7); */
			continue;
		}
		set_msg_bit(&idx);
	}
	if (try_cnt == 3)
		return (RESPONSE_FAIL);
	kill(g_conn_stat.client_pid, SIGUSR1);
	return (RESPONSE_SUCCESS);
}

void set_msg_bit(int* idx)
{
	if (g_conn_stat.client_sig == SIGUSR2)
		g_conn_stat.msg[g_conn_stat.msgidx] |= 1 << *idx;
	(*idx)--;
}
