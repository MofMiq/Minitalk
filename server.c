/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:12:53 by marirodr          #+#    #+#             */
/*   Updated: 2023/03/22 16:30:38 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*esta funcion es la que recibe la señal del cliente. se encarga de recibir el 
mensaje y reconstruir los bytes recibidos (decodificar) para mostarrlos en la
salida estandar.

la funcion se utiliza caracter a caracter (byte a byte)

en el momento en el que el bit esta completo - ya está el char entero en binario-
hacemos dos comprobaciones: si el byte impreso es el ultimo de la cadena (mesaje)
imprimimos un salto de linea manualmente y enviamos al SO/otro proceso?? el 1
con SIGURSR1 con el pid que conseguimos desde la estuctura siginfo_t -> si_pid.
bit = rastrea la posicion del bit actual en el byte recibido
byte = byte actual que se esta decodificando, empieza en 0 siempre que estas 
decodificando el byte, por eso el operador OR para ir sacando los 1s en sus 
posiciones.*/

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

void	ft_decode_message(int signal, siginfo_t *info, void *unused)
{
	static int				bit;
	static unsigned char	byte;

	(void)unused;
	if (signal == SIGUSR1)
		byte = byte | (1 << bit);
	bit++;
	printf("%d", bit);
	if (bit == 8)
	{
		if (byte == '\0')
		{
			ft_printf("\n");
			kill(info->si_pid, SIGUSR1);
		}
		else
			ft_printf("%c", byte);
		bit = 0;
		byte = 0;
	}
}

int	main(void)
{
	struct sigaction	sig;

	display_banner(getpid());
	sig.sa_sigaction = &ft_decode_message;
	sig.sa_flags = SA_SIGINFO;
	//sigemptyset(&sig.sa_mask);
	//sigaddset(&sig.sa_mask, SIGUSR1);
	//sigaddset(&sig.sa_mask, SIGUSR2);
	while (1)
	{
		sigaction(SIGUSR1, &sig, NULL);
		sigaction(SIGUSR2, &sig, NULL);
		pause();
	}
	return (0);
}
