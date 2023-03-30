/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:27:09 by marirodr          #+#    #+#             */
/*   Updated: 2022/11/21 13:00:10 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

int		ft_printf(const char *format, ...);
void	ft_printchar(char c, int *count);
void	ft_printstr(char *str, int *count);
void	ft_printnbr(int nb, int *count);
void	ft_printunsigned(unsigned int nb, int *count);
void	ft_printhex(unsigned long h, int *count, char x);
void	ft_printpointer(void *ptr, int *count);

#endif