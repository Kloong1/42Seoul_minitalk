/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_recieve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <42.4.yohkim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 20:01:19 by yohkim            #+#    #+#             */
/*   Updated: 2022/02/22 15:52:11 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	handler_msglen(int signo, siginfo_t *siginfo, void *context)
{
	(void)context;
	if (g_conn_stat.client_pid != siginfo->si_pid)
	{
		kill(siginfo->si_pid, SIGUSR2);
		return ;
	}
	if (signo == SIGUSR2)
		g_conn_stat.msglen |= 1 << g_conn_stat.bitidx;
	g_conn_stat.bitidx--;
	if (g_conn_stat.bitidx < 0)
	{
		print_msglen();
		ready_to_recieve_msg();
	}
	kill(g_conn_stat.client_pid, SIGUSR1);
}

void	handler_msg(int signo, siginfo_t *siginfo, void *context)
{
	(void)context;
	if (g_conn_stat.client_pid != siginfo->si_pid)
	{
		kill(siginfo->si_pid, SIGUSR2);
		return ;
	}
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
		print_msg();
		free(g_conn_stat.msg);
		init_conn_stat();
		listen();
		return ;
	}
	kill(g_conn_stat.client_pid, SIGUSR1);
}

void	ready_to_recieve_msg(void)
{
	g_conn_stat.bitidx = 7;
	sigaction(SIGUSR1, &g_conn_stat.sa_struct_msg, NULL);
	sigaction(SIGUSR2, &g_conn_stat.sa_struct_msg, NULL);
	g_conn_stat.msg = malloc(sizeof(char) * (g_conn_stat.msglen));
	if (!g_conn_stat.msg)
	{
		ft_putstr_fd("Memory allocation failed!\nProgram exit.", 1);
		exit(EXIT_FAILURE);
	}
}
