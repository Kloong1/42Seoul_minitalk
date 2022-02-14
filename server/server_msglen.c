/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_msglen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <42.4.yohkim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 20:01:19 by yohkim            #+#    #+#             */
/*   Updated: 2022/02/14 23:14:05 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

#include <stdio.h>

t_conn_stat g_conn_stat;

int recieve_msglen()
{
	int try_cnt;
	int idx;
	int unslept_sec;

	try_cnt = 0;
	idx = 31;
	while (try_cnt < 3 && idx >= 0)
	{
		unslept_sec = sleep(3);
		if (unslept_sec == 0 && idx == 31)
			return (RESPONSE_NORESP);
		if (unslept_sec == 0 && idx < 31)
		{
			retry_recieve(&try_cnt, &idx, 31);
			continue;
		}
		set_msglen_bit(&idx);
	}
	if (try_cnt == 3)
		return (RESPONSE_FAIL);
	g_conn_stat.msg = malloc(sizeof(char) * g_conn_stat.msglen + 1);
	if (!g_conn_stat.msg)
		return (RESPONSE_FAIL);
	kill(g_conn_stat.client_pid, SIGUSR1);
	return (RESPONSE_SUCCESS);
}

void set_msglen_bit(int* idx)
{
	if (g_conn_stat.client_sig == SIGUSR2)
		g_conn_stat.msglen |= 1 << *idx;
	(*idx)--;
}

void retry_recieve(int* try_cnt, int* idx, int maxidx)
{
	printf("Retry\n");
	(*try_cnt)++;
	(*idx) = maxidx;
	kill(g_conn_stat.client_pid, SIGUSR2);
}

void handler_msglen(int signo, siginfo_t* siginfo, void* context)
{
	(void)context;

	if (g_conn_stat.client_pid != siginfo->si_pid)
		return;

	g_conn_stat.client_sig = signo;
}

