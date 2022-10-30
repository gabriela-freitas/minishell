/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <mfreixo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 20:05:51 by gafreita          #+#    #+#             */
/*   Updated: 2022/10/30 19:12:09 by mfreixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	finds the quotes given by c, (" or ') in str, starting in pos = i
	pos is given as pointer so its value is altered to be used in next_arg
	returns -1 if no quotes were found (they were open but not closed)
*/
static int	check_quotes(char *str, char c, int *i)
{
	char	*aux;
	int		j;

	j = *i;
	if (!str[j])
		return (-1);
	if (str[j])
	{
		ft_memmove(&str[j], &str[j + 1], ft_strlen(&str[j + 1]) + 1);
		if (c == '\"')
			aux = ft_strchr(&str[j], c);
		else
			aux = ft_strchr(&str[j], c);
		if (!aux)
			return (-1);
		*i += ft_strlen(&str[j]) - ft_strlen(aux);
		ft_memmove(aux, aux + 1, ft_strlen(aux + 1) + 1);
	}
	else
		return (-1);
	return (0);
}

/*returns the next arg, it can end in valid space, be delimited by ", '*/
char	*next_arg(char *str, int index)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] && !ft_isspace(str[i]) && !ft_isquote(str[i]) && !ft_redirec(str[i]))
			i++;
		if (ft_redirec(str[i]))
			check_redirec(str, i, index);
		if (!str[i] || ft_isspace(str[i]) || ft_redirec(str[i]))
			return (ft_substr(str, 0, i));
		else if (ft_isquote(str[i]))
		{
			if (check_quotes(str, str[i], &i) == -1)
				return (0);
			if (!str[i])
				return (ft_substr(str, 0, i));
			continue ;
		}
		i++;
		if (!str[i])
			return (ft_substr(str, 0, i));
	}
	return (NULL);
}

/*	Auxiliar function to make split_command pass the norminette! */
static void	split_aux(char *aux1, char ***split, int index)
{
	int		i;
	int		k;
	// printf("AQUI = %s\n", str);
	char	*aux;

	i = 0;
	k = 0;
	while (aux1[i])
	{
		aux = next_arg(&aux1[i], index);
		if (!aux1)
		{
			free_split(*split);
			*split = NULL;
			break ;
		}
		i += ft_strlen(aux);
		add_split(split, &k, aux);
		if (!aux1[i])
			break ;
		i++;
	}
}

/*	returns an array of args, first is the command to be executed,
	then it's its argumentsnt i
	this is the last parsing, args are ready to be executed
*/
static char	**split_command(char **str, int index)
{
	char	**split;
	char	*aux1;

	aux1 = *str;
	split = malloc(sizeof(char *) * 2);
	split[0] = '\0';
	split_aux(aux1, &split, index);
	return (split);
}

void check_input(int index);


/*	given the list of commands (a command ends with pipe
	of end of input from terminal),
	splits it, into valid arguments and executes
*/
void	second_parse(void)
{
	t_list	*temp;
	int		i;

	i = -1;
	temp = base()->div_pipes;
	base()->num_pipes = ft_lstsize(temp);
	base()->pipes = malloc(sizeof(t_pipex) * base()->num_pipes);
	while (temp)
	{
		temp->content = expand((char *)temp->content);
		base()->pipes[++i].redir = FALSE;
		base()->pipes[i].output = malloc(sizeof(char*) * 2);
		base()->pipes[i].output[0] = NULL;
		base()->pipes[i].output_nb = 0;
		base()->pipes[i].input = malloc(sizeof(char*) * 2);
		base()->pipes[i].input[0] = NULL;
		base()->pipes[i].input_nb = 0;
		base()->pipes[i].heredoc = NULL;
		base()->pipes[i].cmds = split_command((char **)&temp->content, i);
		check_input(i);
		temp = temp->next;
	}
}

void check_input(int index)
{
	int		i;
	char	*input;

	i = 0;
	input = NULL;
	while (base()->pipes[index].input[i])
	{
		if (access(base()->pipes[index].input[i], F_OK) < 0)
		{
			// parse_error_message(file, ": No such file or directory", 1);
			input = ft_strdup(base()->pipes[index].input[i]);
			break ;
		}
		i++;
	}
	if (input == NULL && base()->pipes[index].input_nb != 0)
		input = ft_strdup(base()->pipes[index].input[i - 1]);
	free_split(base()->pipes[index].input);
	base()->pipes[index].input = malloc(sizeof(char*) * 2);
	base()->pipes[index].input[0] = input;
	base()->pipes[index].input[1] = NULL;
}
