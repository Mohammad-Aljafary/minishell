SRC =   src/main.c \
		\
		src/utils/join_args.c \
		src/utils/move_command_to_head.c \
		\
		src/lists/list_token.c \
		src/lists/list_env.c \
		src/lists/clear_lists.c \
		src/lists/create_lists_env_exp.c \
		\
		src/parse/tokenizer.c \
		src/parse/parser.c \
		\
		src/execution/execute.c \
		src/execution/execute_external.c\
		\
		src/redirections/out_redirection.c\
		src/redirections/in_redirection.c \
		src/redirections/heredoc.c \
		src/redirections/apply_heredoc.c \
		src/redirections/expand_heredoc.c \
		\
		src/built-ins/built_in.c \
		src/built-ins/cd.c \
		src/built-ins/echo.c\
		src/built-ins/env.c \
		src/built-ins/exit.c \
		src/built-ins/export.c\
		src/built-ins/export_util.c\
		src/built-ins/pwd.c \
		src/built-ins/unset.c \
		\
		src/expands/expander.c \
		src/expands/expander_utils.c\
		src/expands/expander_util_2.c \
		src/expands/expander_util_3.c \
		src/expands/expander_util_4.c \
		src/expands/replaces.c
