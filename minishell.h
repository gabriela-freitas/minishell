/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:49:25 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/01 18:57:23 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "libft.h"
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum 
{ 
    ECHO, 
    CD, 
    PWD,
    EXPORT, 
    ENV, 
    EXIT, 
    UNSET,
} built;

void	inthandler(int sig);
void	read_loop(void);
void    parser(char *str);
int     ft_issapce(char c);
int     check_cmd(char *str);
int     ft_isBuiltIn(char *cmd);





#endif
