/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 20:59:39 by rbalbous          #+#    #+#             */
/*   Updated: 2019/09/17 23:57:54 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int			main(int argc, char **argv)
{
	t_args	args;
	t_infos	infos;

	args = (t_args){0, 0, 0, 0, 0, 1, 0, 0};
	infos = (t_infos){-1, 3, 0};
	parser(argc, argv, &args, &infos);
	return (0);
}
