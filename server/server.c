/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <42.4.yohkim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 13:57:28 by yohkim            #+#    #+#             */
/*   Updated: 2022/02/12 15:10:04 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>

int flag = 0;

void signal_handler(int signo, siginfo_t* siginfo, void* context)
{
	(void)context;

	printf("signo = %d\n", signo);
	if (signo == SIGUSR1)
	{
		usleep(100);
		kill(siginfo->si_pid, SIGUSR1);
	}
}

int main()
{
	printf("%d\n", getpid());

	struct sigaction sa_struct;
	sa_struct.sa_flags = SA_SIGINFO;
	sa_struct.sa_sigaction = signal_handler;
	sigemptyset(&sa_struct.sa_mask);

	sigaction(SIGUSR1, &sa_struct, NULL);
	sigaction(SIGUSR2, &sa_struct, NULL);

	while (1) pause();
}
