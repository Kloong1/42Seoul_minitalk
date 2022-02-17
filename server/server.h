/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <42.4.yohkim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:55:11 by yohkim            #+#    #+#             */
/*   Updated: 2022/02/17 18:35:02 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef struct t_queue
{
	pid_t			queue[100];
	int				frontidx;
	int				rearidx;
	unsigned int	capacity;
	unsigned int	size;
}	t_queue;

typedef struct t_conn_stat
{
	pid_t				client_pid;
	char				*msg;
	size_t				msglen;
	unsigned int		msgidx;
	int					bitidx;
	t_queue				queue;
	struct sigaction	sa_struct_listen;
	struct sigaction	sa_struct_msglen;
	struct sigaction	sa_struct_msg;
}	t_conn_stat;

extern t_conn_stat	g_conn_stat;

void	init_conn_stat(void);
void	init_sa_structs(void);
void	init_queue(void);
void	listen(void);
void	ready_to_recieve_msglen(void);
void	ready_to_recieve_msg(void);
void	handler_listen(int signo, siginfo_t *siginfo, void *context);
void	handler_msglen(int signo, siginfo_t *siginfo, void *context);
void	handler_msg(int signo, siginfo_t *siginfo, void *context);
void	enqueue_client(pid_t client_pid);
int		is_queue_empty(void);
int		is_queue_full(void);
void	enqueue(pid_t client_pid);
pid_t	dequeue(void);
void	print_pid(pid_t pid);
void	print_msglen(void);
void	print_msg(void);

#endif
