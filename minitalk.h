/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:08:58 by marirodr          #+#    #+#             */
/*   Updated: 2023/03/27 15:22:33 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include "ft_printf/ft_printf.h"
# include "libft/libft.h"

//bash -c 'for c in {0..255}; do tput setaf $c; tput setaf $c | cat -v;
//    echo =$c; done' -> color palette linux

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define WHITE "\033[0;97m"
# define BLUE "\033[0;36m"
# define END "\033[0m"
# define BACK "\033[45m"

#endif