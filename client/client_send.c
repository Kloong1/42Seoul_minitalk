/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_send.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <42.4.yohkim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 22:06:24 by yohkim            #+#    #+#             */
/*   Updated: 2022/02/14 23:31:48 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

#include  <stdio.h>

t_conn_stat g_conn_stat;

void send_bits_sig(unsigned int val, unsigned int bitlen)
{
	unsigned int bitmask;

	bitmask = 1 << (bitlen - 1);
	while (bitmask > 0)
	{
		usleep(150);
		if ((val & bitmask) == 0)
			kill(g_conn_stat.server_pid, SIGUSR1);
		else
			kill(g_conn_stat.server_pid, SIGUSR2);
		bitmask = bitmask >> 1;
	}
}

int send_msglen()
{
	int try_cnt;
	int response;

	try_cnt = 0;
	while(try_cnt < 3)
	{
		send_bits_sig(g_conn_stat.msglen, 32);
		response = wait_response(SIGUSR1, SIGUSR2, 5);
		if (response == RESPONSE_SUCCESS || response == RESPONSE_FAIL)
			return (response);
		try_cnt++;
	}

	return (RESPONSE_FAIL);
}

int send_msg()
{
	int try_cnt;
	int response;

	while (g_conn_stat.msgidx < g_conn_stat.msglen)
	{
		try_cnt = 0;
		/* printf("try cnt = %d msgidx = %d\n", try_cnt, g_conn_stat.msgidx); */
		while(try_cnt < 3)
		{
			send_bits_sig(g_conn_stat.msg[g_conn_stat.msgidx], 8);
			response = wait_response(SIGUSR1, SIGUSR2, 5);
			if (response == RESPONSE_SUCCESS)
				break;
			if (response == RESPONSE_FAIL)
				return (RESPONSE_FAIL);
			try_cnt++;
		}
		if (try_cnt == 3)
			return (RESPONSE_FAIL);
		g_conn_stat.msgidx++;
	}
	return (RESPONSE_SUCCESS);
}
