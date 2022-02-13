/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <42.4.yohkim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:10:09 by yohkim            #+#    #+#             */
/*   Updated: 2022/02/12 16:58:46 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "client.h"

#include <stdio.h>

t_conn_stat g_conn_stat;

/* void convert_and_send_char(pid_t server_pid, char c)
 * {
 *     unsigned char bitmask;
 *
 *     bitmask = 1 << 7;
 *
 *     printf("Send %c: ", c);
 *     for (int i = 0; i < 8; i++)
 *     {
 *         if ((c & (bitmask >> i)) == 0)
 *         {
 *             kill(server_pid, SIGUSR1);
 *             printf("0");
 *         }
 *         else
 *         {
 *             kill(server_pid, SIGUSR2);
 *             printf("1");
 *         }
 *         usleep(50);
 *     }
 *     printf("\n");
 * } */

void handler_get_response(int signo)
{
	g_conn_stat.response = signo;
}

int wait_response(int signo, int maxtry, int usec)
{
	int sleep_result;
	int trycnt;

	sleep_result = -1;
	trycnt = 0;
	while (g_conn_stat.response != signo && sleep_result != 0 && trycnt < maxtry)
	{
		sleep_result = usleep(usec);
		trycnt++;
	}

	if (sleep_result == 0 || trycnt == maxtry)
		return (-1);

	return (0);
}

int connect()
{
	signal(SIGUSR1, handler_get_response);
	signal(SIGUSR2, handler_get_response);

	kill(g_conn_stat.server_pid, SIGUSR1);

	return (wait_response(SIGUSR1, 3, 1000000));
}

void init_conn_stat(pid_t server_pid, char* msg)
{
	g_conn_stat.server_pid = server_pid;
	g_conn_stat.response = -1;
	g_conn_stat.msg = msg;
	g_conn_stat.msglen = strlen(msg);
	g_conn_stat.msgidx = 0;
}

int send_msg_len()
{
	unsigned int bitmask;

	bitmask = 1 << 31;
	while (bitmask > 0)
	{
		if ((g_conn_stat.msglen & bitmask) == 0)
			kill(g_conn_stat.server_pid, SIGUSR1);
		else
			kill(g_conn_stat.server_pid, SIGUSR2);
		bitmask = bitmask >> 1;
		usleep(100);
	}

	if (wait_response(SIGUSR1, 1, 10000) < 0)
		return (-1);

	//재송신 시도하는거 짜야함
	return (0);
}

int main(int argc, char* args[])
{
	if (argc != 3)
		return (1);

	init_conn_stat(atoi(args[1]), args[1]);

	if (connect() == -1)
		return (1);

	if (send_msg_len() == -1)
		return (1);

	/* if (send_msg() == -1)
	 *     return (1); */

	return (0);
}

