/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llethuil <llethuil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:51:13 by llethuil          #+#    #+#             */
/*   Updated: 2022/05/16 16:57:09 by llethuil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	prepare_exec(t_input *input, t_cmd_lst *cmd);
static void	launch_exec(t_input *input, t_cmd_lst *cmd);
static void	update_underscore(t_input *input);

void	executer(t_input *input, t_cmd_lst *cmd)
{
	if (prepare_exec(input, cmd) == FAILED)
		return ;
	if (input->cmd_exec_tab[0][0])
	{
		launch_exec(input, cmd);
		update_underscore(input);
	}
}

static int	prepare_exec(t_input *input, t_cmd_lst *cmd)
{
	if (handle_heredocs(input, cmd) == FAILED)
		return (FAILED);
	if (open_all_pipes(cmd) == FAILED)
	{
		close_all_pipes(cmd);
		return (FAILED);
	}
	if (open_all_files(input, cmd, PARENT) == FAILED)
		g_status = 1;
	return (SUCCESS);
}

static void	launch_exec(t_input *input, t_cmd_lst *cmd)
{
	if (input->n_cmd == 1 && cmd_is_built_in(cmd->name) == YES)
	{
		set_stdout(input, cmd);
		g_status = exec_built_in(input, cmd);
		if (ft_strcmp(cmd->name, "exit") == SUCCESS)
		{
			clear_all_gb(&input->gb);
			exit(g_status);
		}
		dup2(STDIN_FILENO, STDOUT_FILENO);
	}
	else
		g_status = pipe_exec(input, cmd);
}

static void	update_underscore(t_input *input)
{
	char	*underscore_value;
	int		i;

	underscore_value = NULL;
	i = -1;
	if (input->n_cmd == 1)
	{
		while (input->cmd_exec_tab[0][++i])
			;
		underscore_value = ft_strdup(input, input->cmd_exec_tab[0][i - 1]);
		input->gb->type = ENV_STRUCT;
		change_value(input, "_", underscore_value);
	}
}
