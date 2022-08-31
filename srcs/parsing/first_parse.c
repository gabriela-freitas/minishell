/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 17:42:29 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/31 16:44:32 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	remove_spaces(const char *str);

/*	checks if all open single quotes are closed
	returns 0 if they are closed and 1 otherwise,
	backslash are ignored
*/
static int	check_single_quotes(char *line)
{
	char	*aux;
	int		open_quotes;
	int		back_slash;

	aux = line;
	open_quotes = FALSE;
	while (*aux)
	{
		back_slash = 0;
		while (*aux && *aux == '\\' && aux++)
			back_slash++;
		if (*aux && *aux == '\"' && open_quotes == FALSE && back_slash % 2 == 0)
			aux = ft_strchr_valid(aux + 1, '\"');
		if (!aux || !*aux)
			return (TRUE);
		if (back_slash % 2 == 0 && *aux == '\'')
			open_quotes = (open_quotes + 1) % 2;
		aux++;
	}
	return (open_quotes);
}

/*	function to make search_quotes function pass
	the norminette
*/
static void	search_quotes_aux(char *line, int i,
	int *open_quotes, int back_slash)
{
	static char	c;

	if (ft_isquote(line[i]))
	{
		if (*open_quotes == TRUE && line[i] != c)
			return ;
		c = line[i];
		if (c == '\'')
		{
			if (open_quotes == FALSE && back_slash % 2 == 0)
				*open_quotes = (*open_quotes + 1) % 2;
		}
		else if (i > 0)
		{
			if (line[i - 1] != '\\' || back_slash % 2 == 0)
				*open_quotes = (*open_quotes + 1) % 2;
		}
		else
			*open_quotes = (*open_quotes + 1) % 2;
	}
}

/*	checks if open quotes are closed,
	\" is not considered valid double quotes
	returns 0 if they close, 1 otherwise
*/
static int	search_quotes(char *line)
{
	int		open_quotes;
	int		back_slash;
	int		i;

	i = -1;
	back_slash = 0;
	open_quotes = FALSE;
	if (check_single_quotes(line) == TRUE)
		return (TRUE);
	while (line[++i])
	{
		while (line[i] == '\\' && i++)
			back_slash++;
		if (!line[i])
			break ;
		search_quotes_aux(line, i, &open_quotes, back_slash);
		back_slash = 0;
	}
	return (open_quotes);
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
	if (search_quotes(line))
	{
		parse_error_message("", "unfinished input", 2);
		return (0);
	}
	if (!search_pipes(line))
		return (0);
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
