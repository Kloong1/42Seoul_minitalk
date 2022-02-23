/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <42.4.yohkim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 13:57:28 by yohkim            #+#    #+#             */
/*   Updated: 2022/02/22 16:24:06 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_conn_stat	g_conn_stat;

int	main(void)
{
	init_conn_stat();
	init_sa_structs();
	listen();
	while (1)
	{
		if (sleep(10) == 0 && g_conn_stat.isConnected == 1)
		{
			ft_putstr_fd("No response from client. Disconnect.\n", 1);
			if (g_conn_stat.msg != NULL)
				free(g_conn_stat.msg);
			init_conn_stat();
			listen();
		}
	}
}

void	init_conn_stat(void)
{
	g_conn_stat.client_pid = 0;
	g_conn_stat.msg = NULL;
	g_conn_stat.msglen = 0;
	g_conn_stat.msgidx = 0;
	g_conn_stat.bitidx = 0;
	g_conn_stat.isConnected = 0;
}

void	init_sa_structs(void)
{
	g_conn_stat.sa_struct_listen.sa_flags = SA_SIGINFO;
	g_conn_stat.sa_struct_listen.sa_sigaction = handler_listen;
	sigemptyset(&g_conn_stat.sa_struct_listen.sa_mask);
	g_conn_stat.sa_struct_msglen.sa_flags = SA_SIGINFO;
	g_conn_stat.sa_struct_msglen.sa_sigaction = handler_msglen;
	sigemptyset(&g_conn_stat.sa_struct_msglen.sa_mask);
	sigaddset(&g_conn_stat.sa_struct_msglen.sa_mask, SIGUSR1);
	sigaddset(&g_conn_stat.sa_struct_msglen.sa_mask, SIGUSR2);
	g_conn_stat.sa_struct_msg.sa_flags = SA_SIGINFO;
	g_conn_stat.sa_struct_msg.sa_sigaction = handler_msg;
	sigemptyset(&g_conn_stat.sa_struct_msg.sa_mask);
	sigaddset(&g_conn_stat.sa_struct_msg.sa_mask, SIGUSR1);
	sigaddset(&g_conn_stat.sa_struct_msg.sa_mask, SIGUSR2);
}
