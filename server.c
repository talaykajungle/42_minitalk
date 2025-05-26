/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamutlu <tamutlu@student.42.fr>             +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:37:30 by tamutlu           #+#    #+#             */
/*   Updated: 2025/05/15 17:37:30 by tamutlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

static void singnal_mngmt(int sig)
{

}

// -- Helper function to write character to file descriptor
static void ft_putchar_fd(char c, int fd)
{
	write(1, &c, 1);
}

// -- Helper function to write integer to file descriptor
static void ft_putnbr_fd(int nb, int fd)
{
	unsigned int nbr;

	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nbr = (unsigned int)(nb * -1);
	}
	else
		nbr = (unsigned int)nb;
	if (nb >= 10)
		ft_putchar_fd(nbr / 10, fd);
	ft_putchar_fd((char)(nbr % 10 + 48), fd);
}

int main()
{
}
