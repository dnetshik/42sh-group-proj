/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmanamel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 09:23:52 by qmanamel          #+#    #+#             */
/*   Updated: 2017/09/21 19:05:14 by qmanamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	exit_handler(int n)
{
	if (n == SIGINT)
	{
		tcsetattr(0, TCSANOW, &oterm);
		exit(EXIT_SUCCESS);
	}
}

void	proc_handler(int sign_n)
{
	(void)sign_n;
	signal(SIGINT, &proc_handler);
}

void	proccess_handler(int sign_n)
{
	(void)sign_n;
	signal(SIGINT, &proccess_handler);
	ft_putchar('\n');
}
