/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <42.4.yohkim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:55:11 by yohkim            #+#    #+#             */
/*   Updated: 2022/02/15 14:39:03 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

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
	pid_t client_pid;
	int client_sig;
	char* msg;
	size_t msglen;
	unsigned int msgidx;
	struct sigaction sa_struct;
} t_conn_stat;

extern t_conn_stat g_conn_stat;

void init_conn_stat();
void set_sigaction(int signo, void (*sighandler)(int, siginfo_t*, void*));
void listen(int client_sig);
int recieve_msglen();
void set_msglen_bit(int* idx);
void set_msg_bit(int* idx);
void set_bit(unsigned int* val, int idx);
void retry_recieve(int* try_cnt, int* idx, int maxidx);
void end_recieve_msglen();
void handler_listen(int signo, siginfo_t* siginfo, void* context);
void handler_msglen(int signo, siginfo_t* siginfo, void* context);
int recieve_msg();
int recieve_msg_char();

#endif
