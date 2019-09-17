/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 14:56:20 by rbalbous          #+#    #+#             */
/*   Updated: 2019/09/17 15:21:18 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H

# define FT_SSL_H

# include "ft_printf.h"

/*
** DEFINE COMMANDS
*/
# define MDC_NB 2
# define MDC_LINE {"md5", "sha256"}
# define CMD_NB 4
# define CMD_LINE {"", "md5", "sha256", "base64"}


# define USAGE "[md5;sha256] [-pqr] [-s string] [files ...]\n"

typedef struct s_args		t_args;
typedef struct s_infos		t_infos;
typedef unsigned char		t_uint8;
typedef struct s_file_queue	t_file_queue;
typedef struct s_hash_md5	t_hash;
typedef struct s_sha		t_sha;
typedef struct s_base		t_base;

struct		s_args
{
	t_uint8 arg_q: 1;
	t_uint8 arg_p: 1;
	t_uint8 arg_s: 1;
	t_uint8 arg_r;
	t_uint8 arg_d: 1;
	t_uint8 arg_e: 1;
	t_uint8 arg_i: 1;
	t_uint8 arg_o: 1;
	t_uint8 arg_nf: 1;
};

struct s_infos
{
	t_int32 md;
	t_int32 error;
	t_uint32 len;
};


struct		s_hash_md5
{
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;
	uint32_t aa;
	uint32_t bb;
	uint32_t cc;
	uint32_t dd;
};

struct		s_sha
{
	uint32_t h0;
	uint32_t h1;
	uint32_t h2;
	uint32_t h3;
	uint32_t h4;
	uint32_t h5;
	uint32_t h6;
	uint32_t h7;
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;
	uint32_t e;
	uint32_t f;
	uint32_t g;
	uint32_t h;
	uint32_t ch;
	uint32_t s0;
	uint32_t s1;
	uint32_t maj;
	uint32_t tmp1;
	uint32_t tmp2;
};

struct		s_base
{
	uint8_t h0;
	uint8_t h1;
	uint8_t h2;
	uint8_t h3;
};

void			parser(int argc, char **argv, t_args *args, t_infos *infos);
int				disp_usage();
void			disp_usage_exit();
void			disp_usage_ssl_exit(char *str);
void			disp_usage_ssl(char *str);
void			md5(t_args *args, t_infos *infos, char *str, char *file);
void			sha256(t_args *args, t_infos *infos, char *str, char *file);
void			treat_file(t_args *args, t_infos *infos, char *file, int fd);
int				get_flags_args(t_args *args, t_infos *infos, char **str, int argc);
char			*split_args(int ac,char **av);
int				parse_md(t_args *args, t_infos *infos, char **str, int argc);
int				parse_base64(t_args *args, t_infos *infos, char **str, int argc);
void			do_hash(t_args *args, t_infos *infos, char *str, char *file);
void			base64(t_args *args, t_infos *infos, char *str, char *file);
#endif
