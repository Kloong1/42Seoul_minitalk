/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_listen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <42.4.yohkim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:12:15 by yohkim            #+#    #+#             */
/*   Updated: 2022/02/22 15:55:16 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	listen(void)
{
	sigaction(SIGUSR1, &g_conn_stat.sa_struct_listen, NULL);
	sigaction(SIGUSR2, &g_conn_stat.sa_struct_listen, NULL);
	ft_putstr_fd("Listening...\nServer ", 1);
	print_pid(getpid());
}

void	handler_listen(int signo, siginfo_t *siginfo, void *context)
{
	(void)context;
	if (signo != SIGUSR1)
		return ;
	g_conn_stat.client_pid = siginfo->si_pid;
	g_conn_stat.bitidx = 31;
	g_conn_stat.isConnected = 1;
	sigaction(SIGUSR1, &g_conn_stat.sa_struct_msglen, NULL);
	sigaction(SIGUSR2, &g_conn_stat.sa_struct_msglen, NULL);
	ft_putstr_fd("Connected with client - ", 1);
	print_pid(g_conn_stat.client_pid);
	kill(g_conn_stat.client_pid, SIGUSR1);
}
