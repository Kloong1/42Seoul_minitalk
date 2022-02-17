/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_queue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <42.4.yohkim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 13:54:25 by yohkim            #+#    #+#             */
/*   Updated: 2022/02/17 13:55:03 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_conn_stat g_conn_stat;

int is_queue_empty(void)
{
	return (g_conn_stat.queue.size == 0);
}

int is_queue_full(void)
{
	return (g_conn_stat.queue.size == g_conn_stat.queue.capacity);
}

void enqueue(pid_t client_pid)
{
	g_conn_stat.queue.rearidx = (g_conn_stat.queue.rearidx + 1) % 100;
	g_conn_stat.queue.size++;
	g_conn_stat.queue.queue[g_conn_stat.queue.rearidx] = client_pid;
}

pid_t dequeue(void)
{
	g_conn_stat.queue.frontidx = (g_conn_stat.queue.frontidx + 1) % 100;
	g_conn_stat.queue.size--;
	return (g_conn_stat.queue.queue[g_conn_stat.queue.frontidx]);
}
