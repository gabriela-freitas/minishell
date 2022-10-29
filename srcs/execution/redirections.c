/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 11:02:01 by gafreita          #+#    #+#             */
/*   Updated: 2022/10/29 16:50:29 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//open files
//redirect outputs
//make heredoc

/* allocs memory to an array of strings that will store the HEREDOC */
static void recursive_heredoc(t_pipex *command, char ***out_heredoc, int i)
{
	char	*line;

	line = readline("heredoc> ");
	if (!ft_strncmp(line, (char *)command->heredoc, ft_strlen(line) + 1))
	{
		*out_heredoc = malloc(sizeof(char *) * (i + 1));
		if (!(*out_heredoc))
		{
			parse_error_message("Malloc", "error", errno);
			return ;
		}
		free(line);
		line = NULL;
	}
	else
		recursive_heredoc(command, out_heredoc, i + 1);
	printf(">>>>>>>>>>>>\n");
	(*out_heredoc)[i] = line;
}

/* writes the content of heredoc in a pipe and changes the content of heredoc
var to the pipe_fd instead of the delimiter string
FIXME: REMEMBER TO FREE*/
static void	*pipe_heredoc(t_pipex *command, char **out_heredoc)
{
	int	*fd_heredoc;

	if (!out_heredoc)
		return (NULL);
	fd_heredoc =  malloc(sizeof(int) * 2);
	if (pipe(fd_heredoc) < 0)
	{
		parse_error_message("Pipe", "Could not create pipe", errno);
		return (NULL);
	}
	close(fd_heredoc[0]);
	while (*out_heredoc)
	{
		ft_putendl_fd(*out_heredoc, fd_heredoc[1]);
		out_heredoc++;
	}
	free_split(out_heredoc);
	free(command->heredoc);
	command->heredoc = (void *)fd_heredoc;
	return (command->heredoc);
}

/* Define where the command will read its output:
	If < , its a file
	If << , its the heredoc (READ end of the pipe)
	else , the standard input */
static int	open_infiles(t_pipex *cmd)
{
	char **out_heredoc;

	out_heredoc = NULL;
	if (cmd->input)
	{
		cmd->fd[IN] = open(cmd->input, O_RDONLY | O_ASYNC, 0644);
		if (cmd->fd[IN] < 0)
		{
			parse_error_message(cmd->input, ": No such file or directory", 1);
			return (FALSE);
		}
	}
	else if (cmd->heredoc)
	{
		recursive_heredoc(cmd, &out_heredoc, 0);
		if (!pipe_heredoc(cmd, out_heredoc))
			return (FALSE);
		close(((int *)cmd->heredoc)[1]);
		cmd->fd[IN] = ((int *)cmd->heredoc)[0];
	}
	else
		cmd->fd[IN] = STD;
	return (TRUE);
}

/* Define where the command will write its output:
	If specified, open outfiles, and the last one will be the new output fd
	Otherwise, it will be the standard output*/
static int	open_outfiles(t_pipex *cmd)
{
	int		i;

	if (cmd->output)
	{
		i = -1;
		while (cmd->output[++i])
		{
			cmd->fd[OUT] = open(cmd->output[i], O_WRONLY | O_ASYNC | O_TRUNC | O_CREAT, 0644);
			if (cmd->fd[OUT] < 0)
			{
				parse_error_message(cmd->output[i], "Could not open file", 1);
				return (FALSE);
			}
		}
	}
	else
		cmd->fd[OUT] = STD;
	return (TRUE);
}
/// @brief
/// @param command
/// @return
//TODO: check erros return
void	open_files(t_pipex *cmd)
{
	open_infiles(cmd);
	printf("infiles done\n");
	open_outfiles(cmd);
	printf("outfiles done\n");
}
