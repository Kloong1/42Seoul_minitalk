/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_send.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <42.4.yohkim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 22:06:24 by yohkim            #+#    #+#             */
/*   Updated: 2022/02/15 15:26:25 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

#include  <stdio.h>

t_conn_stat g_conn_stat;

int send_bit_and_wait_response(unsigned int val, unsigned int bitidx)
{
	int try_cnt;
	int response;
	unsigned int bitmask;

	try_cnt = 0;
	bitmask = 1 << bitidx;
	while(try_cnt < 3)
	{
		if ((val & bitmask) == 0)
			kill(g_conn_stat.server_pid, SIGUSR1);
		else
			kill(g_conn_stat.server_pid, SIGUSR2);
		response = wait_response(SIGUSR1, NOSIG, 1);
		if (response == RESPONSE_SUCCESS || response == RESPONSE_FAIL)
			return (response);
		try_cnt++;
	}
	return (RESPONSE_FAIL);
}

int send_msglen()
{
	int response;
	int bitidx;

	bitidx = 31;
	while (bitidx >= 0)
	{
		response = send_bit_and_wait_response(g_conn_stat.msglen, bitidx--);
		if (response == RESPONSE_FAIL)
			return (RESPONSE_FAIL);
		usleep(150);
	}
	return (RESPONSE_SUCCESS);
}

int send_msg()
{
	int response;
	int bitidx;

	bitidx = 7;
	while (g_conn_stat.msgidx < g_conn_stat.msglen)
	{
		response = send_bit_and_wait_response(g_conn_stat.msg[g_conn_stat.msgidx], bitidx--);
		if (response == RESPONSE_FAIL)
			return (RESPONSE_FAIL);
		if (bitidx < 0)
		{
			bitidx = 7;
			g_conn_stat.msgidx++;
		}
		usleep(50);
	}
	return (RESPONSE_SUCCESS);
}
