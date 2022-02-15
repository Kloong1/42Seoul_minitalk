/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <42.4.yohkim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:10:09 by yohkim            #+#    #+#             */
/*   Updated: 2022/02/15 14:25:52 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "client.h"

#include <stdio.h>

t_conn_stat g_conn_stat;

void handler_get_response(int signo)
{
	g_conn_stat.response = signo;
}

void init_conn_stat(pid_t server_pid, char* msg)
{
	g_conn_stat.server_pid = server_pid;
	g_conn_stat.response = 0;
	g_conn_stat.msg = msg;
	g_conn_stat.msglen = strlen(msg);
	g_conn_stat.msgidx = 0;
	signal(SIGUSR1, handler_get_response);
	signal(SIGUSR2, handler_get_response);
}

int main(int argc, char* args[])
{
	if (argc != 3)
		return (1);

	init_conn_stat(atoi(args[1]), args[2]);

	printf("PID: %d\n", getpid());

	if (connect() != RESPONSE_SUCCESS)
		return (1);

	if (send_msglen() != RESPONSE_SUCCESS)
		return (1);

	printf("msglen done\n");

	if (send_msg() != RESPONSE_SUCCESS)
	    return (1);

	return (0);
}

