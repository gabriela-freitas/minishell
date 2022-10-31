/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 17:42:29 by gafreita          #+#    #+#             */
/*   Updated: 2022/10/30 23:00:39 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	remove_spaces(const char *str);

/*	checks if all opened quotes are closed */
static int	search_quotes(char *line)
{
	int		open_quotes;
	int		i;
	char	c;

	open_quotes = FALSE;
	i = 0;
	while (line[i])
	{
		if (ft_isquote(line[i]))
		{
			if (open_quotes == FALSE)
			{
				open_quotes = TRUE;
				c = line[i];
			}
			else if (open_quotes == TRUE)
			{
				if (c == line[i])
					open_quotes = FALSE;
			}
		}
		i++;
	}
	return (open_quotes);
}

void	redir_spaces(char *str)
{
	size_t	i;
	char	*aux;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			aux = ft_strchr(&(str[i + 1]), str[i]);
			if (aux)
				i += (size_t)aux - (size_t)(&str[i]);
		}
		if (str[i + 1] && ft_redir(str[i + 1]) && ft_isspace(str[i]))
			ft_memmove((void *)&str[i], (void *)&str[i + 1], \
			ft_strlen(&str[i + 1]) + 1);
		if (str[i + 1] && ft_redir(str[i]) && ft_isspace(str[i + 1]))
			ft_memmove((void *)&str[i + 1], (void *)&str[i + 2], \
			ft_strlen(&str[i + 2]) + 1);
	}
}

//Gabi corrigiu norminette adicionando as variaveis como parametros da funcao
static int	search_redir(char *line, int i, char c, int redir)
{
	while (line[++i])
	{
		if (ft_redir(line[i]))
		{
			if (redir == 0)
			{
				redir = 1;
				c = line[i];
			}
			else if (redir == 1)
			{
				if (c == line[i])
					redir++;
				else
					return (0);
			}
			else
				return (0);
		}
		else
			redir = 0;
	}
	redir_spaces(line);
	return (1);
}

/*Removes extra spaces outside ' ' and " "
	Checks whether the pipe is valid and
	fills the command list (base()->div_pipes)*/
int	first_parse(char *line)
{
	if (*line == '|')
	{
		parse_error_message("", "parse error near `|'", 2);
		return (0);
	}
	if (!remove_spaces(line))
		return (0);
	if (!search_redir(line, -1, 0, 0))
	{
		parse_error_message("", "syntax error near unexpected token `<'", 2);
		return (0);
	}
	if (search_quotes(line))
	{
		parse_error_message("", "unclosed quotes", 2);
		return (0);
	}
	if (!search_pipes(line))
		return (0);
	if (!check_cmds())
		reutrn (0);
	return (1);
}

//remove extra spaces outside " " and ' '
static int	remove_spaces(const char *str)
{
	size_t	i;
	size_t	j;
	char	*aux;

	j = -1;
	while (ft_isspace(str[++j]))
		;
	if (!str[j])
		return (0);
	ft_memmove((void *)str, (void *)&str[j], ft_strlen(&str[j]) + 1);
	i = -1;
	while (str[++i])
	{
		j = i;
		while (ft_isspace(str[j]) && str[j + 1] && ft_isspace(str[j + 1]))
			j++;
		ft_memmove((void *)&str[i], (void *)&str[j], ft_strlen(&str[j]) + 1);
		if (str[i] == '\"' || str[i] == '\'')
		{
			aux = ft_strchr(&(str[i + 1]), str[i]);
			if (aux)
				i += (size_t)aux - (size_t)(&str[i]);
		}
	}
	return (1);
}
