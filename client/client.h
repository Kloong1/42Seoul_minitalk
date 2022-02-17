/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <42.4.yohkim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 15:42:53 by yohkim            #+#    #+#             */
/*   Updated: 2022/02/17 18:26:25 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include "../libft/libft.h"

typedef struct t_conn_stat
{
	pid_t			server_pid;
	int				response;
	char			*msg;
	size_t			msglen;
	unsigned int	msgidx;
	unsigned int	bitidx;
}	t_conn_stat;

extern t_conn_stat	g_conn_stat;

void	init_conn_stat(pid_t server_pid, char *msg);
int		connect(void);
void	send_msg(void);
void	send_bit_signal(unsigned long val, unsigned int bitidx);
void	handler_connect(int signo);
void	handler_wait_queue(int signo);
void	handler_msglen(int signo);
void	handler_msg(int signo);

#endif
