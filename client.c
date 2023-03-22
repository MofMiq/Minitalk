/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:12:48 by marirodr          #+#    #+#             */
/*   Updated: 2023/03/22 16:28:23 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
kill: enviar.
usleep: crear un delay  para que el caracter en binario no se lie y salga 
ordenado.
"imprime" el byte t lo envia. si es un 1 envia  SIGUSR1, si es 0, envia SIGUSR2
*/

void	ft_send_msg(int pid, char byte)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if ((byte & (1 << i)) != 0)
		{
			kill(pid, SIGUSR1);		
		}
		else
			kill(pid, SIGUSR2);
		usleep(50);
		i++;
	}
}

void	ft_handler(int a)
{
	if (a == SIGUSR1)
		ft_printf("The message has been received successfully.");
}

int	main(int argc, char **argv)
{
	int					pid;
	int					i;
	struct sigaction	sig;

	i = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		sig.sa_handler = &ft_handler;
		sigaction(SIGUSR1, &sig, NULL);
		while (argv[2][i] != '\0')
		{
			ft_send_msg(pid, argv[2][i]);
			i++;
		}
		ft_send_msg(pid, '\0');
	}
	else
		ft_printf("Format error: <PID> <text>\n");
	return (0);
}
