/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohkim <42.4.yohkim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:35:32 by yohkim            #+#    #+#             */
/*   Updated: 2022/02/22 16:39:02 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	print_pid(pid_t pid)
{
	ft_putstr_fd("PID: ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putstr_fd("\n", 1);
}

void	print_msglen(void)
{
	ft_putstr_fd("Message length = ", 1);
	ft_putnbr_fd(g_conn_stat.msglen, 1);
	ft_putstr_fd("\n", 1);
}

void	print_msg(void)
{
	ft_putstr_fd("Client message\n", 1);
	ft_putstr_fd(g_conn_stat.msg, 1);
	ft_putstr_fd("\n\n", 2);
}
