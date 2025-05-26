/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamutlu <tamutlu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:24:35 by tamutlu           #+#    #+#             */
/*   Updated: 2025/05/26 19:24:35 by tamutlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
/* Signal handler to process SIGUSR1 and SIGUSR2
   Stores the char being built from bits
   Tracks number of bits received
   If signal is SIGUSR1 (represents bit 1)
   Set least significant bit to 1
   Increment bit counter
   If 8 bits were received (full byte)
   Print char
   Reset char to 0 for next byte
   Reset bit counter to 0 */
void	take_msg(int sig)
{
	static unsigned char	c;
	static int				i;

	if (sig == SIGUSR1)
		c = c | 1;
	i++;
	if (i == 8)
	{
		if (c == 0)
			ft_putstr_fd("\n", 1);
		else
			ft_putchar_fd(c, 1);
		c = 0;
		i = 0;
	}
	c = c << 1;
}
/*
Ensure system calls are restarted if interrupted
Clear signal mask
*/

int	main(void)
{
	struct sigaction	sa;

	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	sa.sa_handler = take_msg;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL)
		== -1)
	{
		ft_putstr_fd("Error setting up sigaction\n", 1);
		return (1);
	}
	while (1)
		pause();
	return (0);
}

// int	main(void)
// {
// 	ft_putstr_fd("Server PID: ", 1);
// 	ft_putnbr_fd(getpid(), 1);
// 	ft_putchar_fd('\n', 1);
// 	signal(SIGUSR1, take_msg);
// 	signal(SIGUSR2, take_msg);
// 	while (1)
// 		pause();
// 	return (0);
// }