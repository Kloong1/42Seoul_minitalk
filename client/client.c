/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <42.4.yohkim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:10:09 by yohkim            #+#    #+#             */
/*   Updated: 2022/02/17 18:15:32 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_conn_stat	g_conn_stat;

void	init_conn_stat(pid_t server_pid, char *msg)
{
	g_conn_stat.server_pid = server_pid;
	g_conn_stat.response = 0;
	g_conn_stat.msg = msg;
	g_conn_stat.msglen = ft_strlen(msg) + 1;
	g_conn_stat.msgidx = 0;
	g_conn_stat.bitidx = 0;
	signal(SIGUSR1, handler_connect);
	signal(SIGUSR2, handler_wait_queue);
}

int	main(int argc, char *args[])
{
	if (argc != 3)
	{
		ft_putstr_fd("Wrong args! Exit.\n", 1);
		return (1);
	}
	init_conn_stat(ft_atoi(args[1]), args[2]);
	if (connect() < 0)
	{
		ft_putstr_fd("Connection failed. Exit.\n", 1);
		return (1);
	}
	send_msg();
	return (0);
}
