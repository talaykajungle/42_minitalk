/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamutlu <tamutlu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 00:22:01 by tamutlu           #+#    #+#             */
/*   Updated: 2025/05/27 00:22:01 by tamutlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
About the function binary:
Sends a string to a process (pid) by converting chars to binary and using signals

Structure of the code:
1. Bit position counter "int i"
2. Loops through each character in the string until null terminator
3. Starts from the most significant bit (bit 7)
4. Processes all 8 bits of the current char
5. Checks if current bit is 1
6. Sends SIGUSR1 for bit 1
7. Sends SIGUSR2 for bit 0
8. Delays to ensure signal processing
9. Moves to next bit
10. Moves to next char
*/

volatile sig_atomic_t	g_ack = 0;

void	ack_handler(int sig)
{
	if (sig == SIGUSR1)
		g_ack = 1;
	else if (sig == SIGUSR2)
		g_ack = 0;
	else
		ft_putstr_fd("Error: Unexpected signal received\n", 2);
}

static void	send_bit(int pid, int bit)
{
	g_ack = 0;
	if (bit)
	{
		if (kill(pid, SIGUSR1) == -1)
		{
			ft_putstr_fd("Error: SIGUSR1\n", 2);
			exit(1);
		}
	}
	else
	{
		if (kill(pid, SIGUSR2) == -1)
		{
			ft_putstr_fd("Error: SIGUSR2\n", 2);
			exit(1);
		}
	}
	while (!g_ack)
		pause();
}

static void	send_char_bits(int pid, unsigned char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		send_bit(pid, (c >> i) & 1);
		i--;
	}
}

static void	send_message(int pid, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		send_char_bits(pid, str[i]);
		i++;
	}
	send_char_bits(pid, '\n');
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					pid;

	sa.sa_handler = ack_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	if (argc != 3)
	{
		ft_putstr_fd("Usage: ./client <PID> <message>\n", 1);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		ft_putstr_fd("Error: Invalid PID\n", 1);
		return (1);
	}
	if (!argv[2][0])
	{
		ft_putstr_fd("Error: Empty message\n", 1);
		return (1);
	}
	send_message(pid, argv[2]);
	return (0);
}
