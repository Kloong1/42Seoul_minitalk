/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_connect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <42.4.yohkim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:12:15 by yohkim            #+#    #+#             */
/*   Updated: 2022/02/15 16:18:31 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

#include <stdio.h>

t_conn_stat g_conn_stat;

void handler_listen(int signo, siginfo_t* siginfo, void* context)
{
	(void)context;

	if (signo != SIGUSR1)
		return;

	g_conn_stat.client_pid = siginfo->si_pid;
	g_conn_stat.bitidx = 31;
	set_sigaction(SIGUSR1, handler_msglen);
	set_sigaction(SIGUSR2, handler_msglen);
	kill(g_conn_stat.client_pid, SIGUSR1);
}

