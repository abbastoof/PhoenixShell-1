/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:00:56 by atoof             #+#    #+#             */
/*   Updated: 2023/05/31 17:35:48 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_token_type(char *str, t_token *token, t_lexer *state)
{
	if (ft_strcmp(str, "|") == 0)
		token[state->token_indx].type = TOKEN_PIPE;
	else if (ft_strcmp(str, "<") == 0)
		token[state->token_indx].type = TOKEN_INPUT;
	else if (ft_strcmp(str, ">") == 0)
		token[state->token_indx].type = TOKEN_OUTPUT;
	else if (ft_strcmp(str, ">>") == 0)
		token[state->token_indx].type = TOKEN_OUTPUT_APPEND;
	else if (ft_strcmp(str, "<<") == 0)
		token[state->token_indx].type = TOKEN_HEREDOC;
	else if (str[0] == '$')
	{
		if (ft_strcmp(str, "$?") == 0)
			token[state->token_indx].type = TOKEN_EXIT_STATUS;
		else
			token[state->token_indx].type = TOKEN_VARIABLE;
	}
	else
	{
		token[state->token_indx].type = TOKEN_CMD;
	}
	token[state->token_indx].value = ft_strdup(str);
	state->token_indx++;
}

// static void	handlequote(t_lexer *state, int type)
// {
// 	int	*flag;

// 	if (type == TOKEN_QUOTE)
// 		flag = &(state->inquote);
// 	else
// 		flag = &(state->indquote);
// 	if (flag == 0)
// 	{
// 		*flag = 1;
// 		state->start = &state->crnt_str[state->indx];
// 	}
// 	else
// 	{
// 		*flag = 0;
// 		assign_new_token();
// 	}
// }

static void	init_info(t_lexer *state, char *line)
{
	state->inquote = 0;
	state->indquote = 0;
	state->indx = 0;
	state->path = NULL;
	state->token_indx = 0;
	state->start = line;
	state->crnt_str = line;
	state->var = NULL;
	state->token = malloc(sizeof(t_token) * 1024);
}

t_token	*lexer(char *line, t_environment *env)
{
	t_lexer	state;

	init_info(&state, line);
	while (state.crnt_str[state.indx])
	{
		if (state.crnt_str[state.indx] == '\'' && !state.indquote)
			is_word(state.crnt_str + state.indx, &state, env, 0);
		else if (state.crnt_str[state.indx] == '\"' && !state.inquote)
			is_word(state.crnt_str + state.indx, &state, env, 1);
		else if (((state.crnt_str[state.indx] == ' ') || (state.crnt_str[state.indx] == '\t'))
			&& (!state.inquote) && (!state.indquote))
		{
			assign_token_type(state.start, state.token, &state);
			state.start = &state.crnt_str[state.indx + 1];
		}
		state.indx++;
	}
	assign_token_type(state.start, &(state.token[state.token_indx]), &state);
	return (state.token);
}

void	process_cmd(char *line, t_environment *env)
{
	t_token	*tokens;

	tokens = lexer(line, env);
	// handle_command(tokens);
}
