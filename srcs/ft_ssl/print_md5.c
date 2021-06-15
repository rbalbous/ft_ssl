/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_md5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 15:20:53 by rbalbous          #+#    #+#             */
/*   Updated: 2020/10/10 15:21:43 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		print_args(t_args *args, char *str, char *file)
{
	if (args->arg_r)
		args->arg_r = 2;
	if (!args->arg_s && !args->arg_p && !args->arg_q && !args->arg_r && file != NULL)
		ft_printf("MD5 (%s) = ", file);
	if (args->arg_p && !args->arg_q && !args->arg_r)
	{
		args->arg_p = 0;
		ft_printf("%s", str);
	}
	if (args->arg_s && !args->arg_q && !args->arg_r) 
	{	
		ft_printf("MD5 (\"%s\") = ", str);
		args->arg_s = 0;
	}
}

void		print_hash(t_hash hash, t_args *args, char *str, char *file)
{
	unsigned char *p;

	p=(unsigned char *)&hash.a;
	ft_printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
    p=(unsigned char *)&hash.b;
	ft_printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
    p=(unsigned char *)&hash.c;
	ft_printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
    p=(unsigned char *)&hash.d;
    ft_printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
	if (args->arg_r && args->arg_s && !args->arg_q)
		ft_printf(" \"%s\"", str);
	if (args->arg_r && file != NULL && !args->arg_q)
		ft_printf(" %s", file);
	ft_printf("\n");
}
