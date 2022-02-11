/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <42.4.yohkim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:10:09 by yohkim            #+#    #+#             */
/*   Updated: 2022/02/10 14:53:44 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void convert_and_send_char(pid_t server_pid, char c)
{
	unsigned char bitmask;
	
	bitmask = 1 << 7;

	printf("Send %c: ", c);
	for (int i = 0; i < 8; i++)
	{
		if ((c & (bitmask >> i)) == 0)
		{
			kill(server_pid, SIGUSR1);
			printf("0");
		}
		else
		{
			kill(server_pid, SIGUSR2);
			printf("1");
		}
		usleep(50);
	}
	printf("\n");
}

void send_msg(pid_t server_pid, char* msg)
{
	while (*msg)
	{
		convert_and_send_char(server_pid, *msg);
		msg++;
	}
}

int main(int argc, char* args[])
{
	if (argc < 3)
		return (1);

	send_msg(atoi(args[1]), args[2]);
}

