/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_connect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <42.4.yohkim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 13:57:50 by yohkim            #+#    #+#             */
/*   Updated: 2022/02/22 16:19:57 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	connect(void)
{
	int	try_cnt;

	print_pid(getpid());
	try_cnt = 0;
	while (try_cnt < 3)
	{
		kill(g_conn_stat.server_pid, SIGUSR1);
		if (sleep(5) != 0 || g_conn_stat.response == SIGUSR1)
			break ;
		try_cnt++;
		ft_putstr_fd("Try again...\n", 1);
	}
	if (try_cnt == 3)
		return (-1);
	return (0);
}

void	handler_connect(int signo)
{
	g_conn_stat.response = signo;
	g_conn_stat.bitidx = 31;
	signal(SIGUSR1, handler_msglen);
	signal(SIGUSR2, handler_msglen);
}

void	handler_wait(int signo)
{
	(void)signo;
	ft_putstr_fd("Waiting...\n", 1);
	sleep(3);
}

void	print_pid(pid_t pid)
{
	ft_putstr_fd("Client PID: ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putstr_fd("\n", 1);
}
