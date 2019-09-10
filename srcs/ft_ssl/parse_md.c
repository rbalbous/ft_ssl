/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_md.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 13:50:24 by rbalbous          #+#    #+#             */
/*   Updated: 2019/09/07 22:31:34 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int				parse_md(char **str, t_args *args, int argc)
{
	ft_printf("parse_md\n");
	if (str == NULL)
	{
		str[argc] = get_prompt();
		do_hash(args, str[0], NULL);
		return (1);
	}
	argc = get_flags_args(args, str, argc);
	return (1);
}
