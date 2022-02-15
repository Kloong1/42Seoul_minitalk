/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <42.4.yohkim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 15:42:53 by yohkim            #+#    #+#             */
/*   Updated: 2022/02/15 14:00:26 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

#define RESPONSE_NORESP -1
#define RESPONSE_SUCCESS 0
#define RESPONSE_FAIL 1
#define RESPONSE_RETRY 2

#define NOSIG -1

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
	unsigned int msgidx;
} t_conn_stat;

extern t_conn_stat g_conn_stat;

int send_msglen();
int send_msg();
void handler_get_response(int signo);
int connect();
int wait_response(int sig_success, int sig_retry, int sec);

#endif
