/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_connect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <42.4.yohkim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 13:57:50 by yohkim            #+#    #+#             */
/*   Updated: 2022/02/14 22:59:20 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

#include  <stdio.h>

t_conn_stat g_conn_stat;

int connect()
{
	int try_cnt;
	int response;

	try_cnt = 0;
	while (try_cnt < 3)
	{
		kill(g_conn_stat.server_pid, SIGUSR1);
		response = wait_response(SIGUSR1, NOSIG, 10);
		if (response == RESPONSE_SUCCESS || response == RESPONSE_FAIL)
			return (response);
		try_cnt++;
	}

	return (RESPONSE_FAIL);
}

int wait_response(int sig_success, int sig_retry, int sec)
{
	int sleep_result;

	sleep_result = sleep(sec);

	if (sleep_result == 0)
		return (RESPONSE_NORESP);
	
	if (g_conn_stat.response == sig_success)
		return (RESPONSE_SUCCESS);

	if (g_conn_stat.response == sig_retry)
		return (RESPONSE_RETRY);

	return (RESPONSE_FAIL);
}
