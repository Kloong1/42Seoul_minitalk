/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <42.4.yohkim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 13:57:28 by yohkim            #+#    #+#             */
/*   Updated: 2022/02/10 23:59:22 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>

int flag = 0;

void signal_handler(int signo)
{
	printf("signo = %d\n", signo);
}

int main()
{
	printf("%d\n", getpid());

	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);

	while (1) pause();
}
