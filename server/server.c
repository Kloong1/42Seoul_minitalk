/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <42.4.yohkim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 13:57:28 by yohkim            #+#    #+#             */
/*   Updated: 2022/02/15 16:13:21 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

#include <stdio.h>

t_conn_stat g_conn_stat;

int main()
{
	printf("PID: %d\n", getpid());

	init_conn_stat();

	while (1)
	{
		listen(SIGUSR1);

		if (recieve_msglen() != RESPONSE_SUCCESS)
		{
			printf("Recieve msglen error!\n");
			init_conn_stat();
			continue;
		}

        printf("msglen = %zu\n", g_conn_stat.msglen);

        if (recieve_msg() != RESPONSE_SUCCESS)
		{
			printf("Recieve msg error!\n");
			init_conn_stat();
			continue;
		}

		for(int i = 0; i < 1000; i++)
			for (int j = 0; j < 1000; j++)
				for (int k = 0; k < 1000; k++);

        init_conn_stat();
	}
}

void init_conn_stat()
{
	g_conn_stat.client_pid = 0;
	g_conn_stat.client_sig = -1;
	g_conn_stat.msg = NULL;
	g_conn_stat.msglen = 0;
	g_conn_stat.msgidx = 0;
	g_conn_stat.sa_struct.sa_flags = SA_SIGINFO;
	sigemptyset(&g_conn_stat.sa_struct.sa_mask);
	set_sigaction(SIGUSR1, handler_listen);
	set_sigaction(SIGUSR2, handler_listen);
}

void set_sigaction(int signo, void (*sighandler)(int, siginfo_t*, void*))
{
	g_conn_stat.sa_struct.sa_sigaction = sighandler;
	sigaction(signo, &g_conn_stat.sa_struct, NULL);
}
