/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:12:53 by marirodr          #+#    #+#             */
/*   Updated: 2023/03/27 15:32:11 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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

/*esta funcion es la que recibe la señal del cliente. se encarga de procesar 
señales mensaje y reconstruir los bytes recibidos (decodificar) para mostrarlos
en la salida estandar.

la funcion se utiliza caracter a caracter (byte a byte)

en el momento en el que el bit esta completo - ya está el char entero en binario-
hacemos dos comprobaciones: si el byte impreso es el ultimo de la cadena (mesaje)
imprimimos un salto de linea manualmente y enviamos al SO/otro proceso?? el 1
con SIGURSR1 con el pid que conseguimos desde la estuctura siginfo_t -> si_pid.
bit = rastrea la posicion del bit actual en el byte recibido
byte = byte actual que se esta decodificando, empieza en 0 siempre que estas 
decodificando el byte, por eso el operador OR para ir sacando los 1s en sus 
posiciones.
 -> kill(info->si_pid, SIGUSR1); //una vez el mensaje finaliza, enviamos una se-
ñal SIGUSR1 al proceso que envio el mensaje para confirmar que lo hemos recibido.
*/

void	ft_decode_message(int signal, siginfo_t *info, void *unused)
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
		else
			ft_printf("%s%c%s", BLUE, byte, END);
		bit = 0;
		byte = 0;
	}
}

/*este programa es un buvle infinito que espera recibir señales de SO. El
programa no hace nada hasta que recibe una señal -por eso pause()-.
En la estructura sigaction, se inicializa la funcion sa_sigaction en la dire-
ccion de memoria de la funcion decode_message, para que sepa que funcion
debe llamar cuando se reciba una señal y que ésta la procese.
La estructura de sigaction se usa para configurar el comportamiento
de la señal.
sigemptyset: inicializa el conjunto de señales vacio
sigaddset: agrega una señal especifica al conjunto de señales
estas funciones se encargan de configurar correctamente la mascara de señales
para evitar recibir señales no deseadas que afecten al la ejecucion normal
del programa.
struct sigaction msg: esta estructura se usa para configurar el comporta-
miento de la señal
msg.sa_sigaction = &ft_decode_message: se establece el miembro 'sa_sigaction'
en la direccion de memoria de la funcion "ft_decode_message", para indicarle 
que ésta debe ser llamada cuando reciba una señal
msg.sa_flags = SA_SIGINFO: se establece la bandera "SA_SIGINFO" para indicar
que queremos utilizar la estructura "siginfo_t" para obtener informacion sobre
la señal.
*/

int	main(void)
{
	struct sigaction	msg;

	display_banner(getpid());
	msg.sa_sigaction = &ft_decode_message;
	msg.sa_flags = SA_SIGINFO;
	while (1)
	{
		sigaction(SIGUSR1, &msg, NULL);
		sigaction(SIGUSR2, &msg, NULL);
		pause();
	}
	return (0);
}

	//sigemptyset(&msg.sa_mask);
	//sigaddset(&msg.sa_mask, SIGUSR1);
	//sigaddset(&msg.sa_mask, SIGUSR2);