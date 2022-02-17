/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <42.4.yohkim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 13:57:28 by yohkim            #+#    #+#             */
/*   Updated: 2022/02/17 18:31:25 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_conn_stat	g_conn_stat;

int	main(void)
{
	init_conn_stat();
	init_sa_structs();
	init_queue();
	listen();
	while (1)
		pause();
}

void	init_conn_stat(void)
{
	g_conn_stat.client_pid = 0;
	g_conn_stat.msg = NULL;
	g_conn_stat.msglen = 0;
	g_conn_stat.msgidx = 0;
	g_conn_stat.bitidx = 0;
}

void	init_sa_structs(void)
{
	g_conn_stat.sa_struct_listen.sa_flags = SA_SIGINFO;
	g_conn_stat.sa_struct_listen.sa_sigaction = handler_listen;
	sigemptyset(&g_conn_stat.sa_struct_listen.sa_mask);
	g_conn_stat.sa_struct_msglen.sa_flags = SA_SIGINFO;
	g_conn_stat.sa_struct_msglen.sa_sigaction = handler_msglen;
	sigemptyset(&g_conn_stat.sa_struct_msglen.sa_mask);
	g_conn_stat.sa_struct_msg.sa_flags = SA_SIGINFO;
	g_conn_stat.sa_struct_msg.sa_sigaction = handler_msg;
	sigemptyset(&g_conn_stat.sa_struct_msg.sa_mask);
}

void	init_queue(void)
{
	g_conn_stat.queue.capacity = 100;
	g_conn_stat.queue.size = 0;
	g_conn_stat.queue.frontidx = -1;
	g_conn_stat.queue.rearidx = -1;
}
