/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 19:47:03 by rbalbous          #+#    #+#             */
/*   Updated: 2019/09/01 16:48:43 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			disp_usage()
{
	ft_dprintf(2, "usage:" USAGE);
}

void			disp_usage_exit()
{
	exit(ft_dprintf(2, "usage:" USAGE));
}

void			disp_usage_ssl_exit(char *str)
{
	exit(ft_dprintf(2, "ft_ssl: Error: '%s' is an invalid command.\n\n", str) +
	ft_dprintf(2, "Standard commands\nbase64\n\nMessage Digest commands\nmd5\nsha256") +
	ft_dprintf(2, "\n\nCipher commands\n\n"));
}

void			disp_usage_ssl(char *str)
{
	ft_dprintf(2, "ft_ssl: Error: '%s' is an invalid command.\n\n", str);
	ft_dprintf(2, "Standard commands\nbase64\n\nMessage Digest commands\nmd5\nsha256");
	ft_dprintf(2, "\n\nCipher commands\n\n");
}
