/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <42.4.yohkim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 15:42:53 by yohkim            #+#    #+#             */
/*   Updated: 2022/02/12 16:23:27 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct t_conn_stat
{
	pid_t server_pid;
	int response;
	char* msg;
	size_t msglen;
	int msgidx;
} t_conn_stat;

#endif
