/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 17:42:29 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/20 22:32:20 by mfreixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_spaces(const char *str);

static int check_single_quotes(char *line)
{
	char	*aux;
	int		open_quotes;

	aux = line;
	open_quotes = FALSE;
	while (*aux)
	{
		if (*aux == '\"' && open_quotes == FALSE)
			aux = ft_strchr_valid(aux + 1, '\"') + 1;
		if (*aux == '\'')
			open_quotes = (open_quotes + 1) % 2;
		aux++;
	}
	return (open_quotes);
}

/*	checks if open quotes are closed
	returns 0 if they close, 1 otherwise
*/
static int	search_quotes(char *line) //Marta estas a verificar quotes no geral e nao se abre e fecha o mesmo tipo de quote
{
	int		open_quotes;
	int		back_slash;
	int		i;
	char	c;

	i = -1;
	back_slash = 0;
	open_quotes = FALSE;
	if (check_single_quotes(line) == TRUE)
		return (TRUE);
	while (line[++i])
	{
		while (line[i] == '\\' && i++)
			back_slash++;
		if (ft_isquote(line[i]))
		{
			if (open_quotes == TRUE && line[i] != c)
				continue;
			c = line[i];
			if (c == '\'')
				open_quotes = (open_quotes + 1) % 2;
			else if (i > 0)
			{
				if (line[i - 1] != '\\' || back_slash % 2 == 0)
					open_quotes = (open_quotes + 1) % 2;
			}
			else
				open_quotes = (open_quotes + 1) % 2;
		}
		back_slash = 0;
	}
	return (open_quotes);
}

/*Removes extra spaces outside ' ' and " "
	Checks whether the pipe is valid and
	fills the command list (base()->div_pipes)*/
void	first_parse(char *line)
{
	if (*line == '|')
	{
		error_message("", "parse error near `|'");
		return ;
	}
	remove_spaces(line);
	if (search_quotes(line))
	{
		ft_putstr_fd("unclosed quotes\n", 2);
		return ;
	}
	search_pipes(line);
}

//remove extra spaces outside " " and ' '
static void	remove_spaces(const char *str)
{
	size_t	i;
	size_t	j;
	char	*aux;

	j = -1;
	while (ft_isspace(str[++j]))
		;
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
}
