#ifndef FT_SSL

# define FT_SSL

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
typedef unsigned char		t_uint8;
typedef struct s_file_queue	t_file_queue;
typedef struct s_hash_md5	t_hash;
typedef struct s_sha		t_sha;

struct		s_args
{
	t_uint8 arg_q: 1;
	t_uint8 arg_p: 1;
	t_uint8 arg_s: 1;
	t_uint8 arg_r;
	t_uint8 arg_nf: 1;
	t_int32 md;
	t_int32 error;
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

void			parser(int argc, char **argv, t_args *args);
int				disp_usage();
void			disp_usage_exit();
void			disp_usage_ssl_exit(char *str);
void			disp_usage_ssl(char *str);
void			md5(t_args *args, char *str, char *file);
void			sha256(t_args *args, char *str, char *file);
void			get_prompt(t_args *args);
int				get_flags_args(t_args *args, char **str, int argc);
char			*split_args(int ac,char **av);
int				parse_md(char **str, t_args *args, int argc);
int				parse_base64(char **str, t_args *args, int argc);
void			do_hash(t_args *args, char *str, char *file);
#endif
