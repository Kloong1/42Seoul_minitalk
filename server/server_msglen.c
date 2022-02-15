/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_msglen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <42.4.yohkim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 20:01:19 by yohkim            #+#    #+#             */
/*   Updated: 2022/02/15 14:40:39 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

#include <stdio.h>

t_conn_stat g_conn_stat;

int recieve_msglen()
{
	int idx;

	idx = 31;
	while (idx >= 0)
	{
		if (sleep(5) == 0)
			return (RESPONSE_NORESP);
		if (g_conn_stat.client_sig == SIGUSR2)
			g_conn_stat.msglen |= 1 << idx;
		idx--;
		kill(g_conn_stat.client_pid, SIGUSR1);
	}
	g_conn_stat.msg = malloc(sizeof(char) * g_conn_stat.msglen + 1);
	if (!g_conn_stat.msg)
		return (RESPONSE_FAIL);
	/* kill(g_conn_stat.client_pid, SIGUSR1); */
	return (RESPONSE_SUCCESS);
}

void handler_msglen(int signo, siginfo_t* siginfo, void* context)
{
	(void)context;

	if (g_conn_stat.client_pid != siginfo->si_pid)
		return;

	g_conn_stat.client_sig = signo;
}

