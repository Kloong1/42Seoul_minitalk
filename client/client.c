/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <42.4.yohkim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:10:09 by yohkim            #+#    #+#             */
/*   Updated: 2022/02/12 15:25:57 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "../libft/libft.h"

#include <stdio.h>

int server_response;

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

void get_server_response(int signo)
{
	server_response = signo;
}

int connect(pid_t server_pid, char* msg)
{
	(void)msg;

	signal(SIGUSR1, get_server_response);
	signal(SIGUSR2, get_server_response);

	kill(server_pid, SIGUSR1);

	int sleep_suspended = -1;
	while (server_response != SIGUSR1 && sleep_suspended != 0)
		sleep_suspended = usleep(1000000);

	printf("sleep_suspended = %d\n", sleep_suspended);

	return sleep_suspended;
}

int main(int argc, char* args[])
{
	if (argc != 3)
		return (1);

	server_response = 0;

	if (connect(atoi(args[1]), args[2]) == 0)
		return (1);

	return (0);
}

