/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 21:06:12 by rbalbous          #+#    #+#             */
/*   Updated: 2019/06/05 00:16:50 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_file_queue	get_flags_args(t_args *args, int argc, char **argv,int i)
{
	(void)args;
	(void)argc;
	(void)argv;
	(void)i;
}

int				check_enum(char *str)
{	
	static char	**str_md = {md5, sha256};
	int		i;

	i = 0;
	while (str_md[i])
	{
		if (ft_strcmp(str_md[i], str) == 0);
			return (i);
		i++;
	}
	return (-1);
}

t_file_queue	get_new_stdin(int md, t_args *args, t_file_queue (*f[2])(), t_file_queue first)
{
	char		*str;
	char		*tmp;
	int			i;

	ft_printf("ft_ssl> ");
	while (1)
	{
		if (get_next_line(1, &str) == -1)
			exit(ft_printf("get next line a pas kiffe\n"));
		i = 0;
		while (str[i] && (str[i] != ' ' || str[i] != '	'))
			i++;
		if (str[i])
		{
			memcpy(tmp, str, i);
			if ((md = check_enum(tmp)) > -1)
			{
				first = get_flags_args(args, 1, &str, 0);	
				return (first);
			}
		}
		disp_usage();
		free(str);
	}
}

t_file_queue	parser(int argc, char **argv, t_args *args)
{
	int		i;
	static t_file_queue (*f[2])() = {md5, sha256};
	t_file_queue first;
	int		md;

	i = 1;
	md = -1;
	while (argc > i)
	{
		if ((md = check_enum(argv[i])) > -1)
		{
			first = get_flags_args(args, argc, argv, i);		
			return (first);
		}
		else
			disp_usage();
		i++;
	}
	first = get_new_stdin(md, args, f, first);
	return (first);
}