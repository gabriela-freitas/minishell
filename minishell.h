/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <mfreixo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:49:25 by gafreita          #+#    #+#             */
/*   Updated: 2022/10/30 12:55:30 by mfreixo-         ###   ########.fr       */
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

# define FALSE 0
# define TRUE 1
# define STD -1
# define IN 0
# define OUT 1
# define TEMP_FILE "./.temp"

# define TRUNCATE 0
# define APPEND 1
# define STD -1

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}	t_env;

//CMDS >> the command split in array of string
//input >> file input, NULL if is STDIN
//output >> files outputs, NULL if is STDOUT
//in_mode >> mode in which the input file should be open
//out_mod >> mode in which the output file should be open
//fd >> array with the file descriptors of that command
typedef struct s_pipex
{
	char	**cmds;
	int		num_cmds;
	char	**input;
	char	**output;
	void	*heredoc;
	int		in_mode; 
	int		out_mode;
	int		output_nb;
	int		input_nb;
	int		fd[2];
}	t_pipex;

/*	HOME directory is in base, because when HOME
	is unset cd ~ still goes to HOME directory
	defined in the begining

	base has paths, so it's not needed to search for PATH
	in env before executing each command
*/
typedef struct s_base
{
	t_env	*env;
	char	**paths;
	char	*home;
	char	*oldpwd;
	int		errnumb;
	t_list	*div_pipes;
	t_pipex	*pipes; //array
	int		num_pipes;
}	t_base;

/********* SRCS *********/
//utils.c
void	parse_error_message(char *cmd, char *error, int error_code);
void	error_message(char *cmd, char *arg, char *error, int error_code);
void	command_not_found(char *cmd);
void	sig_block(int sig);
void	sig_block_nl(int sig);

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

//redirections.c
void	open_files(t_pipex *cmd);

/********* PARSING *********/

// expanding.c
void	*expand(char *str);

// first_parsing.c
int		first_parse(char *line);

// parsing_pipes.c
int		search_pipes(char *str);

//second_parse.c
void	second_parse(void);
void	third_parse(void);
char	*next_arg(char *str, int index);

// utils_parsing.c
int		ft_isquote(char c);
void	add_split(char ***split, int *size, char *str);
char	*check_redirec(char *str, int i, int index);
int		ft_redirec(char c);

#endif
