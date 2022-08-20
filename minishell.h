/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:49:25 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/20 01:02:32 by mfreixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "libft.h"
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <sys/wait.h>

enum	e_builtins
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	ENV,
	EXIT,
	UNSET,
};

enum e_operators
{
	NONE,
	PIPE,
	AND,
	OR,
};

# define FALSE 0
# define TRUE 1

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}	t_env;

/*	HOME directory is in base, because when HOME
	is unset cd ~ still goes to HOME directory
	defined in the begining

	base has paths, so it's not needed to search for PATH
	in env before executing each command
*/

typedef struct s_pipex
{
	char	***cmds;
	int		num_cmds;
	int		**pipe_fd;
	int		pipe_aux[2];
} t_pipex;

typedef struct s_base
{
	t_env	*env;
	t_list	*cmds;
	char	**paths;
	char	*home;
	char	*oldpwd;
	int		errnumb;
	t_list	*div_pipes;
	t_pipex	pipe;
}	t_base;

// minishell.c
void	read_loop(void);

//environment.c
t_env	*new_env(char *name, char *content);
void	ini_env(char **env);
void	delone_env(t_env *one_env);
void	env_free(void);

//base.c
void	ini_base(char **env);
t_base	*base(void);
void	base_free(void);

// first_parsing.c
void	first_parse(char *line);

// parsing_pipes.c
void	search_pipes(char *str);

// utils_parsing.c
int		ft_isquote(char c);
char	*ft_strchr_valid(const char *s, int c);
void	my_realloc(char ***split, int size);
void	add_split(char ***split, int *size, char *str);

//second_parse.c
int		ft_special_char(char c);
void	second_parse(void);

// utils.c
int		ft_special_char(char c);

//execute.c
int		execute(char **cmds, int fd);

//export.c
void	export(char **str);
void	unset(char **cmds);

// pwd.c
void	pwd();
void	update_env_pwd(char	*var);


// expanding.c
void expand_str(char *str);
void expand(char **str);



// int     check_cmd(char *str);
char	**get_path();


//utils.c
void	error_message(char *cmd, char *error);
void	error_message_1(char *cmd, char *arg, char *error);


//utils_parsing.c
void	my_realloc(char ***split, int size);

//utils_env.c
char	**convert_env_list(void);
void	export_ordenate(void);
char	*find_env(char	*name);
void	print_env(void);

//builtins.c
int		cd(char *str);
void	ft_exit(char **str);


//env_alter.c
void	change_var(char *name, char *content);

void	ft_echo(char **str);
char	*ft_strchr_valid(const char *s, int c);

//pipex.c
void	control_pipex(void);

#endif
