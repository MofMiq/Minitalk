/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:12:53 by marirodr          #+#    #+#             */
/*   Updated: 2023/03/29 16:12:18 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

void	display_banner(int pid)
{
	ft_printf("\n\t%s██╗   ██╗██╗██╗   ██╗ █████╗     ███╗   ███╗██╗   ██╗██████╗  ██████╗██╗ █████╗\
			%s\n", GREEN, END);
	ft_printf("\t%s██║   ██║██║██║   ██║██╔══██╗    ████╗ ████║██║   ██║██╔══██╗██╔════╝██║██╔══██║\
			%s \n", GREEN, END);
	ft_printf("\t%s██║   ██║██║██║   ██║███████║    ██╔████╔██║██║   ██║██████╔╝██║     ██║███████║\
			%s \n", WHITE, END);
	ft_printf("\t%s╚██╗ ██╔╝██║╚██╗ ██╔╝██╔══██║    ██║╚██╔╝██║██║   ██║██╔══██╗██║     ██║██╔══██║\
			%s\n", WHITE, END);
	ft_printf("\t%s ╚████╔╝ ██║ ╚████╔╝ ██║  ██║    ██║ ╚═╝ ██║╚██████╔╝██║  ██║╚██████╗██║██║  ██║\
			%s\n", GREEN, END);
	ft_printf("\t%s  ╚═══╝  ╚═╝  ╚═══╝  ╚═╝  ╚═╝    ╚═╝     ╚═╝ ╚═════╝ ╚═╝  ╚═╝ ╚═════╝╚═╝╚═╝  ╚═╝\
			%s\n", GREEN, END);
	ft_printf("%s\n\t\t     PID: %d%s\t\t\t%s            By: las chorizo%s\n", RED,
		pid, END, YELLOW, END);
	ft_printf("\t⊱ ──────────────────────────────── {.⋅ ✯ ⋅.} ───────────────────────────────── ⊰\
			\n\n");
}

/*
This function is the one that receives the signal from the client. It's respon-
sible for processing message signals and reconstructing the received bytes (char
by char) to display them on the standard output (decode).

At the moment when the bit is complete - the entire character in binary is
present - we check if the printed byte is the last one in the message chain. 
If so, we manually print a newline and send the SIGUSR1 signal to the other
process (client) with the PID obtained from the siginfo_t structure (si_pid).
This is done to indicate to the process that sent the message that it has 
been received.

bit tracks the current bit position in the received byte, and byte is the current
byte being decoded. It starts at 0 every time a byte is decoded, which is why the
OR operator is used to extract the 1s in their positions.
*/

void	ft_decode_msg(int signal, siginfo_t *info, void *unused)
{
	static int				bit;
	static unsigned char	byte;

	(void)unused;
	if (signal == SIGUSR1)
		byte = byte | (1 << bit);
	bit++;
	if (bit == 8)
	{
		if (byte == '\0')
		{
			ft_printf("\n");
			kill(info->si_pid, SIGUSR1);
		}
		ft_printf("%c", byte);
		bit = 0;
		byte = 0;
	}
}

/*
This program is an infinite loop that waits to receive signals from the
client, and meanwhile does nothing until it receives a signal thanks to the
use of pause().
In the sigaction structure (msg), the sa_sigaction member is initialized to the
memory address of the ft_decode_msg function, so that it knows which function to
call when a signal is received and how it should be processed.

The sigaction structure is used to configure the behavior of the signal.
msg.sa_flags = SA_SIGINFO sets the "SA_SIGINFO" flag to indicate that we want to
use the siginfo_t structure to obtain information about the signal (PID).
*/

int	main(void)
{
	struct sigaction	msg;

	display_banner(getpid());
	msg.sa_sigaction = &ft_decode_msg;
	msg.sa_flags = SA_SIGINFO;
	while (1)
	{
		sigaction(SIGUSR1, &msg, NULL);
		sigaction(SIGUSR2, &msg, NULL);
		pause();
	}
	return (0);
}
