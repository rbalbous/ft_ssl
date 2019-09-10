/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 19:47:03 by rbalbous          #+#    #+#             */
/*   Updated: 2019/09/04 20:16:31 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int			us()
{
	ft_dprintf(2, "usage:" USAGE);
	return (0);
}

int			us_exit()
{
	exit(ft_dprintf(2, "usage:" USAGE));
	return (0);
}

int			us_ssl_exit(char *str)
{
	exit(ft_dprintf(2, "ft_ssl: Error: '%s' is an invalid command.\n\n", str) +
	ft_dprintf(2, "Standard commands\nbase64\n\nMessage Digest commands\nmd5\nsha256") +
	ft_dprintf(2, "\n\nCipher commands\n\n"));
	return (0);
}

int			us_ssl(char *str)
{
	ft_dprintf(2, "ft_ssl: Error: '%s' is an invalid command.\n\n", str);
	ft_dprintf(2, "Standard commands\nbase64\n\nMessage Digest commands\nmd5\nsha256");
	ft_dprintf(2, "\n\nCipher commands\n\n");
	return (0);
}

int			disp_usage(t_args *args)
{
	static int		(*error[4])() = {us_ssl, us_ssl_exit, us, us_exit};

	error[args->error]();
	return (0);
}
