/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:12:48 by marirodr          #+#    #+#             */
/*   Updated: 2023/03/28 13:00:03 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
This function sends a message in the form of a byte of data between different 
processes. The function operates by iterating over the bits in the byte parameter
and sending a signal to a process based on the value of each bit. Specifically,
for each bit in the byte, the function checks whether it is a 1 or a 0. If it is
a 1, the function sends the SIGUSR1 signal to the process. If it is a 0, the fun-
ction sends the SIGUSR2 signal. After each signal is sent, the function waits
for a short period of time using the usleep function before moving on to the 
next bit.
*/

void	ft_send_msg(int pid, char byte)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if ((byte & (1 << i)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(40);
		i++;
	}
}

/*
This function is used as a signal handler. If it receives a SIGUSR1 signal, it
displays a message indicating that the message has been received correctly by
the server
*/

void	ft_handler(int a)
{
	if (a == SIGUSR1)
		ft_printf("%sThe message has been received successfully.%s\n", GREEN,
			END);
}

/*The program receives two arguments in the command line: the PID and a text.
The PID is converted to an integer using ft_atoi. In addition, a sigaction
structure (msg) is created that points to the signal handler ft_handler, and
the sig structure is initialized to configure the behavior of the SIGUSR1 signal
using the sigaction function. When the server sends the SIGUSR1 signal, the 
ft_handler function is executed, indicating that the message has been received
correctly by the server. Then, each character of the text is sent using the 
ft_send_msg function. When all the characters of the message have been sent, 
a null character is sent to indicate the end of the message.*/

int	main(int argc, char **argv)
{
	int					pid;
	int					i;
	struct sigaction	msg;

	i = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		msg.sa_handler = &ft_handler;
		sigaction(SIGUSR1, &msg, NULL);
		while (argv[2][i] != '\0')
		{
			ft_send_msg(pid, argv[2][i]);
			i++;
		}
		ft_send_msg(pid, '\0');
	}
	else
		ft_printf("%sFormat error: <PID> <text>%s\n", RED, END);
	return (0);
}
