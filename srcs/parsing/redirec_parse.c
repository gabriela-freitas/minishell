/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 20:05:51 by gafreita          #+#    #+#             */
/*   Updated: 2022/10/31 14:08:30 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	add_redirec(char redir, int flag, char *file, int index)
{
	base()->pipes[index].redir = TRUE;
	if (redir == '>')
	{
		add_split(&base()->pipes[index].output,
			&base()->pipes[index].output_nb, file);
		if (flag == 1)
			base()->pipes[index].out_mode = O_WRONLY
			| O_ASYNC | O_APPEND | O_CREAT;
		else
			base()->pipes[index].out_mode = O_WRONLY
			| O_ASYNC | O_TRUNC | O_CREAT;
	}
	else
	{
		if (flag == 1)
			base()->pipes[index].heredoc = file;
		else
		{
			add_split(&base()->pipes[index].input,
				&base()->pipes[index].input_nb, file);
			base()->pipes[index].in_mode = O_RDONLY | O_ASYNC;
		}
	}
	return (0);
}

void	check_redirec(char *str, int i, int index)
{
	int		redir;
	int		j;
	int		begin;
	char	*file;

	j = i + 1;
	redir = 0;
	if (str[j] && ft_redir(str[j]) && ++j)
		redir = 1;
	begin = j;
	while (str[j] && !ft_isspace(str[j]) && !ft_redir(str[j]))
		j++;
	if (str[j] && ((str[j + 1] && ft_redir(str[j + 1])) || ft_redir(str[j])))
	{
		file = ft_substr(str, begin, j - begin);
		add_redirec(str[i], redir, file, index);
		ft_memmove(&str[i], &str[j], ft_strlen(&str[j - 1]) + 1);
		check_redirec(str, i, index);
	}
	else if (!str[j] || ft_isspace(str[j]))
	{
		file = ft_substr(str, begin, j - begin);
		add_redirec(str[i], redir, file, index);
		ft_memmove(&str[i], &str[j], ft_strlen(&str[j - 1]) + 1);
	}
}

void	check_input(int index)
{
	int		i;
	char	*input;

	i = 0;
	input = NULL;
	while (base()->pipes[index].input[i])
	{
		if (access(base()->pipes[index].input[i], F_OK) < 0)
		{
			input = ft_strdup(base()->pipes[index].input[i]);
			break ;
		}
		i++;
	}
	if (input == NULL && base()->pipes[index].input_nb != 0)
		input = ft_strdup(base()->pipes[index].input[i - 1]);
	free_split(base()->pipes[index].input);
	base()->pipes[index].input = malloc(sizeof(char *) * 2);
	base()->pipes[index].input[0] = input;
	base()->pipes[index].input[1] = NULL;
}
