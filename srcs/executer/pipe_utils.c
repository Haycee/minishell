/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llethuil <llethuil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 09:48:30 by llethuil          #+#    #+#             */
/*   Updated: 2022/05/04 19:01:33 by llethuil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	open_all_pipes(t_cmd_lst *cmd)
{
	t_cmd_lst	*start;
	int			i;

	i = -1;
	start = cmd;
	while (cmd)
	{
		if (open_single_pipe(cmd->cmd_pipe) == FAILED)
			return (FAILED);
		if (cmd->next == NULL)
			break ;
		cmd = cmd->next;
	}
	cmd = start;
	return (0);
}

void	close_all_pipes(t_cmd_lst *cmd)
{
	int	i;

	i = -1;
	while (cmd->previous)
		cmd = cmd->previous;
	while (cmd)
	{
		close_single_pipe(cmd->cmd_pipe);
		if (cmd->n_heredoc)
			close_single_pipe(cmd->heredoc_pipe);
		cmd = cmd->next;
	}
}
