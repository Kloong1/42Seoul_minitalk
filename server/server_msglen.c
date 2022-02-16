/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_msglen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <42.4.yohkim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 20:01:19 by yohkim            #+#    #+#             */
/*   Updated: 2022/02/16 15:04:52 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

#include <stdio.h>

t_conn_stat g_conn_stat;

void handler_msglen(int signo, siginfo_t* siginfo, void* context)
{
	(void)context;

	if (g_conn_stat.client_pid != siginfo->si_pid)
		return;

	if (signo == SIGUSR2)
		g_conn_stat.msglen |= 1 << g_conn_stat.bitidx;
	g_conn_stat.bitidx--;

	if (g_conn_stat.bitidx < 0)
	{
		printf("msglen = %zu\n", g_conn_stat.msglen);
		g_conn_stat.bitidx = 7;
		set_sigaction(SIGUSR1, handler_msg);
		set_sigaction(SIGUSR2, handler_msg);
		g_conn_stat.msg = malloc(sizeof(char) * (g_conn_stat.msglen + 1));
		if (!g_conn_stat.msg)
			exit(1); //여기는 에러시 처리하고 exit()하는 함수 따로 짜서 그거 호출
	}

	kill(g_conn_stat.client_pid, SIGUSR1);
}

void handler_msg(int signo, siginfo_t* siginfo, void* context)
{
	(void)context;

	if (g_conn_stat.client_pid != siginfo->si_pid)
		return;

	if (signo == SIGUSR2)
		g_conn_stat.msg[g_conn_stat.msgidx] |= 1 << g_conn_stat.bitidx;
	g_conn_stat.bitidx--;

	if (g_conn_stat.bitidx < 0)
	{
		g_conn_stat.bitidx = 7;
		g_conn_stat.msgidx++;
	}

	if (g_conn_stat.msgidx == g_conn_stat.msglen)
	{
		g_conn_stat.msg[g_conn_stat.msgidx] = '\0';
		printf("%s\n", g_conn_stat.msg);
		return;
	}

	kill(g_conn_stat.client_pid, SIGUSR1);
}
