/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 21:06:12 by rbalbous          #+#    #+#             */
/*   Updated: 2019/06/09 20:25:00 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			disp_usage()
{
	ft_printf("erreur\n");
}

void		get_flags_args(t_args *args, char *str, char **str_md)
{
	int		i;
	int		count;

	i = ft_strlen(str_md[(int)args->md]);
	while (str[i])
	{
		count = 0;
		while (str[i] != ' ')
		{
			if (str[i] == '-' && count == 0)
			{
				i++;
				if (str[i] == '-')
				{
					args->arg_nf = 1;
					i++;
				}
				else
				{
					while (str[i] && str[i] != ' ')
					{
						if (str[i] == 'p')
							get_prompt(str, i, args);
						else if (str[i] == 'q')
							args->arg_q = 1;
						else if (str[i] == 's')
							args->arg_s = 1;
						else if (str[i] == 'r')
							args->arg_r = 1;
						else
							disp_usage_exit();
						i++;
					}
				}
			}
		}
		i++;
	}
}

int				check_mdarg(char *str, char **str_md)
{
	int			i;

	i = 0;
	ft_printf("%s\n", str);
	while (str_md[i])
	{
		if (ft_strcmp(str_md[i], str) == 0)
		{
			ft_printf("%d\n", i);
			return (i);
		}
		i++;
	}
	return (-1);
}

void		*get_new_stdin(t_args *args, char **str_md)
{
	char		*str;
	char		*tmp;
	int			i;

	tmp = NULL;
	ft_printf("ft_ssl> ");
	while (1)
	{
		if (get_next_line(1, &str) == -1)
			exit(ft_printf("get next line a pas kiffe\n"));
		i = 0;
		while (str[i] && (str[i] != ' ' || str[i] != '	'))
			i++;
		tmp = ft_memacpy(str, i);
		if ((args->md = check_mdarg(tmp, str_md)) > -1)
		{
			get_flags_args(args, str, str_md);
		}
		else
		{
			disp_usage();
			ft_printf("ft_ssl> ");
		}
		free(str);
	}
}

char		*split_args(int ac,char **av)
{
	int		i;
	char 	*str;
	int		count;
	int		j;

	i = 2;
	count = 0;
	j = 0;
	str = NULL;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			count++;
			j++;
		}
		count++;
		i++;
	}
	count--;
	str = ft_memacpy(av[2], count);
	i = 0;
	while (i < count)
	{
		if (str[i] == 0)
		{
			str[i] = ' ';
		}
		i++;
	}
	return (str);
}

void		parser(int argc, char **argv, t_args *args)
{
	char *str;
	static char *str_md[2] = {"md5", "sha256"};

	if ((args->md = check_mdarg(argv[1], str_md)) > -1)
	{
		str = split_args(argc, argv);
		get_flags_args(args, str, str_md);	
	}
	else
		disp_usage();
	get_new_stdin(args, str_md);
}