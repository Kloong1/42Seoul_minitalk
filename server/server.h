/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <42.4.yohkim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:55:11 by yohkim            #+#    #+#             */
/*   Updated: 2022/02/22 15:34:00 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef struct t_conn_stat
{
	pid_t				client_pid;
	char				*msg;
	size_t				msglen;
	unsigned int		msgidx;
	int					bitidx;
	int					isConnected;
	struct sigaction	sa_struct_listen;
	struct sigaction	sa_struct_msglen;
	struct sigaction	sa_struct_msg;
}	t_conn_stat;

extern t_conn_stat	g_conn_stat;

void	init_conn_stat(void);
void	init_sa_structs(void);
void	listen(void);
void	ready_to_recieve_msg(void);
void	handler_listen(int signo, siginfo_t *siginfo, void *context);
void	handler_msglen(int signo, siginfo_t *siginfo, void *context);
void	handler_msg(int signo, siginfo_t *siginfo, void *context);
void	print_pid(pid_t pid);
void	print_msglen(void);
void	print_msg(void);

#endif
