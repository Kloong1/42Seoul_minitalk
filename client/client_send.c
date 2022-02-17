/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_send.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <42.4.yohkim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 22:06:24 by yohkim            #+#    #+#             */
/*   Updated: 2022/02/17 18:00:12 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_conn_stat g_conn_stat;

void handler_msglen(int signo)
{
	(void)signo;
	if (g_conn_stat.bitidx == 0)
	{
		g_conn_stat.bitidx = 7;
		signal(SIGUSR1, handler_msg);
		signal(SIGUSR2, handler_msg);
		send_bit_signal(g_conn_stat.msglen, 0);
		return;
	}
	send_bit_signal(g_conn_stat.msglen, g_conn_stat.bitidx--);
}

void handler_msg(int signo)
{
	(void)signo;
	usleep(50);
	if (g_conn_stat.bitidx == 0)
	{
		g_conn_stat.bitidx = 7;
		g_conn_stat.msgidx++;
		send_bit_signal(g_conn_stat.msg[g_conn_stat.msgidx - 1], 0);
		if (g_conn_stat.msgidx == g_conn_stat.msglen)
			exit(1); //종료 함수
		return;
	}
	send_bit_signal(g_conn_stat.msg[g_conn_stat.msgidx], g_conn_stat.bitidx--);
}

void send_bit_signal(unsigned long val, unsigned int bitidx)
{
	if ((val & (1 << bitidx)) == 0)
		kill(g_conn_stat.server_pid, SIGUSR1);
	else
		kill(g_conn_stat.server_pid, SIGUSR2);
}

void send_msg(void)
{
	handler_msglen(SIGUSR1);
	while (1)
		pause();
}
