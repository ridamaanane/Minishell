/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <ridamaanane@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:08:19 by hfakou            #+#    #+#             */
/*   Updated: 2025/07/31 15:36:16 by rmaanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parce.h"

char	*join_and_free_two(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

/*
 ** Collects and joins consecutive word-like tokens that are 
 **			not separated by spaces.
 ** Expands environment variables when appropriate,
 **			 except inside single-quoted tokens.
 **
 ** @param lexer - pointer to the current lexer state
 ** @param env 	 - the enviriment linked liste for expanding
 ** @return      - new allocated string representing the
 **			joined and processed word
 */

char	*collect_joined_words(t_lexer *lexer, t_env *env)
{
	char	*word;
	char	*if_var;
	char	*processed;
	t_token	next_tok;
	t_token	tok;

	word = ft_strdup("");
	while (1)
	{
		tok = lexer_next_token(lexer);
		if_var = ft_strndup(tok.literal, tok.len);
		if (tok.type == TOK_SINGLE || !ft_strchr(if_var, '$'))
			processed = if_var;
		else if (ft_strchr(if_var, '$'))
		{
			processed = expand_variable(if_var, env);
			free(if_var);
		}
		word = join_and_free_two(word, processed);
		next_tok = lexer_peek_next_token(lexer);
		if ((next_tok.type != TOK_WORD && next_tok.type != TOK_SINGLE
				&& next_tok.type != TOK_DOUBLE) || next_tok.space == true)
			break ;
	}
	return (word);
}

int	check_for_red(t_token tok)
{
	if (tok.type == TOK_APPAND || tok.type == TOK_OUTPUT
		|| tok.type == TOK_INPUT || tok.type == TOK_HERDOC)
		return (1);
	return (0);
}

/*
 ** Parses the input from the lexer and builds a linked list of commands.
 ** Handles command arguments, redirections (including heredocs), and pipes.
 **
 ** @param lexer - pointer to the lexer containing the token stream
 ** @return      - pointer to the head t_cmd list
 */

t_cmd	*build_cmd_list(t_lexer *lexer, t_env *env)
{
	t_cmd	*head;
	t_cmd	*cmd;
	t_token	tok;

	head = create_cmd();
	cmd = head;

	
	while (1)
	{
		tok = lexer_peek_next_token(lexer);
		if (tok.type == TOK_WORD || tok.type == TOK_DOUBLE || tok.type == TOK_SINGLE)
			add_to_argv(cmd, collect_joined_words(lexer, env));
		else if (check_for_red(tok))
			redirect_del(&tok, cmd, lexer, env);
		else if (tok.type == TOK_PIPE)
		{
			cmd->next = create_cmd();
			cmd = cmd->next;
			tok = lexer_next_token(lexer);
		}
		else if (tok.type == TOK_NULL)
			break ;
	}
	return (head);
}
