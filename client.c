/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:12:48 by marirodr          #+#    #+#             */
/*   Updated: 2023/03/27 15:35:13 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
kill: enviar.
usleep: crear un delay que permite que el receptor tenga tiempo suficiente para
procesar la señal.
"descompone" el byte y lo envia al server. se definen las señales SIGUSR1 y
SIGUSR2:si es un 1 envia  SIGUSR1, si es 0, envia SIGUSR2
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

/*esta funcion se utiliza como manejador de señales. si recibe uan señal SIGUSR1
muestra un mensaje indicando  que el mensaje ha sido recibido correctamente por
el server.*/

void	ft_handler(int a)
{
	if (a == SIGUSR1)
		ft_printf("%sThe message has been received successfully.%s\n", GREEN,
			END);
}

/*el programa recibe dos argumentos en la linea de comando: el pid y un texto.
cconvertimos el pid en un entero con ft_atoi. ademas, se crea una estructura
'sigaction' (msg) que apunta al manejador de señales ft_handler y se inicializa
la estructura 'sig' para configurar el comportamiento de la señal SIGUSR1 
utilizando al funcion 'sigaction' -en este caso, para que cuando reciba del
server la señal SIGUSR1, que significa que el mensaje ha terminado de recibirse
, que ejecute la funcion 'ft_handler'. luego se envia
cada caracter del texto utilizando la funcion 'ft_send_msg'. Cuando todos los
caracteres del mensaje se han enviado, se envia un caracter nulo para indicar
el final del mismo.*/

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
