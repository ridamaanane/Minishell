/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <ridamaanane@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 12:15:36 by rmaanane          #+#    #+#             */
/*   Updated: 2025/08/02 12:15:36 by rmaanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
#define EXECUTION_H

#include "../libft/libft.h"
#include "../lexer/parce.h"
#include "../lexer/lexer.h"
#include "builtins/builtins.h"
#include <errno.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <readline/readline.h>

//utils
void free_split_content(char **array);
char *get_cmd_path(char *cmd, t_env *env);
char **env_to_envp(t_env *env);
void free_envp(char **envp);

//pipe_executor
void pipe_executor(t_cmd *cmd, t_env **env);

//dup_utils
int check_fd(int fd, t_redir *redir);
void dup_fd_out(int fd);
void dup_fd_inp(int fd);
int safe_dup(int oldfd);

//redirection
int find_redirection(t_redir *redir);

//main
int is_builtin(t_cmd *cmd);
int exec_builtin(t_cmd *cmd, t_env **env);

//main_helpers
int	has_pipe(t_cmd *cmd);
void	skip_empty_cmd(t_cmd *cmd);
int	handle_redirect_only(t_cmd *cmd);
int	handle_builtin(t_cmd *cmd, t_env **env);


#endif
