/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 20:05:51 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/25 19:56:31 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	adds the string *add to *str, in position = pos
	output is substr(str, 0, pos) + add + &str[pos]
*/
static void	subs_str(char **str, char *add, int pos, int len)
{
	char	*last;
	char	*first;
	char	*join;

	ft_memmove(&(*str)[pos], &(*str)[pos + len + 1],
		ft_strlen(&(*str)[pos + len + 1]) + 1);
	if (!add)
		return ;
	last = ft_substr(*str, pos, ft_strlen(&(*str)[pos]));
	first = ft_substr(*str, 0, pos);
	join = ft_strjoin(first, add);
	free(*str);
	*str = ft_strjoin(join, last);
	free(join);
	free(last);
	free(first);
	free(add);
}

/*	if variable has spaces, this funcion adds \\ before,
	so it is not considered a new
	argument when spliting commands
*/
void	add_spaces(char **str)
{
	int		i;
	int		j;
	char	*aux;

	i = -1;
	j = 0;
	if (!str || !(*str))
		return ;
	while ((*str)[++i])
		if (ft_isspace((*str)[i]))
			j++;
	aux = malloc(sizeof(char) * (ft_strlen((*str)) + j + 1));
	i = 0;
	j = 0;
	while ((*str)[i])
	{
		if (ft_isspace((*str)[i]))
			aux[j++] = '\\';
		aux[j++] = (*str)[i++];
	}
	aux[j] = '\0';
	free(*str);
	*str = ft_strdup(aux);
	free(aux);
}

/*	receives the position in *str, after $ where the new variable starts
	expands it and alters *str, to change the variable name to its content
*/
int	expand_one(char **str, int pos, int len)
{
	char	*content;
	char	*name;
	int		new_pos;

	name = ft_substr(*str, pos, len);
	if (!ft_strncmp(name, "?", 2))
		content = ft_itoa((base()->errnumb));
	else
		content = ft_strdup(find_env(name));
	free(name);
	if (content)
		add_spaces(&content);
	else
		ft_memmove(&(*str)[pos], &(*str)[pos + 1],
			ft_strlen(&(*str)[pos + 1]) + 1);
	new_pos = ft_strlen(content);
	subs_str(str, content, pos -1, len);
	return (new_pos);
}

/*
	*str at position pos has a $
	this function searches for the end of argument's and
	expands it
*/
void	next_exp(char **str, int *pos)
{
	int	i;
	int	j;

	i = *pos;
	while ((*str)[i] && !ft_special_char((*str)[i]))
		i++;
	if ((*str)[i++] == '$')
	{
		j = i;
		while ((*str)[i] && !ft_special_char((*str)[i])
			&& !ft_isspace((*str)[i]))
			i++;
	}
	if ((*str)[i] == '?')
	{
		*pos += expand_one(str, j, 1);
	}
	else
		*pos += expand_one(str, j, i - j);
}

/*	changes the value of *str to its expanded version - when a valid $ is found
	we change $NAME for its content in env
*/
void	*expand(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] != '$' && str[i] != '\'')
			i++;
		if (str[i] == '\'')
		{
			while (str[++i] != '\'')
				;
			i++;
		}
		else if (str[i] == '$')
		{
			if (!str[i + 1] || (ft_special_char(str[i + 1])
					&& str[i + 1] != '?')
				|| (ft_isspace(str[i + 1])))
				i++;
			else
				next_exp(&str, &i);
		}
	}
	return ((void *)str);
}
