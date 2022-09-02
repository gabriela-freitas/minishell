/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:49:25 by gafreita          #+#    #+#             */
/*   Updated: 2022/09/02 10:55:13 by mfreixo-         ###   ########.fr       */
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
# include <fcntl.h>

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
}	t_pipex;

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

/********* SRCS *********/
// minishell.c
void	read_loop(void);

//utils.c
void	parse_error_message(char *cmd, char *error, int error_code);
void	error_message(char *cmd, char *arg, char *error, int error_code);
void	command_not_found(char *cmd);
int		ft_special_char(char c);
void	sig_block(int sig);

/********* BASE *********/
//base.c
t_base	*base(void);
void	ini_base(char **env);
void	free_command_line(void);
void	base_free(void);

//environment.c
t_env	*new_env(char *name, char *content);
void	ini_env(char **env);
void	delone_env(t_env *one_env);
void	env_free(void);

/********* BUILTINS *********/
//cd.c
int		cd(char **args);

//echo.c
void	ft_echo(char **str);

//env.c
void	env(char **args);
char	**convert_env_list(void);
char	*find_env(char	*name);

//exit.c
void	ft_exit(char **args);

//export.c
void	change_var(char *name, char *content);
void	export(char **str);

// pwd.c
void	pwd(void);
void	update_env_pwd(char	*var);

//unset.c
void	unset(char **cmds);

//utils_export.c
void	export_ordenate(void);

/********* EXECUTION *********/
//execute.c
int		execute(char **cmds, int fd);
void	exec_all(void);

//pipex.c
void	loop_pipex(void);

/********* PARSING *********/

// expanding.c
void	*expand(char *str);

// first_parsing.c
int		first_parse(char *line);

// parsing_pipes.c
int		search_pipes(char *str);

//second_parse.c
void	second_parse(void);

// utils_parsing.c
int		ft_isquote(char c);
void	add_split(char ***split, int *size, char *str);

#endif
