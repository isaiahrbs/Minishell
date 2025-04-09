# Makefile

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -g

# Include directory
INCLUDES = -Iinc

# Object directory
OBJ_DIR = obj

# Source files
SRCS = lexing/get_input.c lexing/tokenize.c lexing/init_type.c \
	functions/linked_lists/add_back.c functions/linked_lists/new_token.c \
	main.c functions/strings/ft_split.c functions/strings/ft_split_utils.c \
	functions/strings/check_var.c functions/strings/is_equal.c \
	cleaner/assignment.c cleaner/expansion.c cleaner/expansion_utils.c \
	functions/strings/ft_strdup.c functions/linked_lists/free_list.c \
	functions/linked_lists/free_token_list.c functions/strings/ft_calloc.c \
	signals/signals.c functions/strings/ft_strjoin.c \
	functions/debug/print_chained_list.c cleaner/ft_env.c \
	lexing/filter.c lexing/filter_utils.c executing/executing.c \
	executing/real_split.c executing/find_path.c executing/check_types.c \
	executing/pipe_fork.c parsing/command_list.c parsing/check_if_valid.c \
	functions/linked_lists/free_command_list.c functions/strings/is_metachar.c \
	functions/debug/printcmdlist.c cleaner/unset_var.c \
	functions/strings/ft_itoa.c executing/built_in.c builtins/cd.c \
	executing/executing_utils.c builtins/heredoc.c parsing/command_list_utils.c

# Object files (preserving directory structure)
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Executable name
TARGET = Minishell

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ -lreadline

# Compile source files to object files
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean up build files
clean:
	rm -rf $(OBJ_DIR)

# Clean up build files and executable
fclean: clean
	rm -f $(TARGET)

# Rebuild target: cleans and builds all.
re: fclean all

.PHONY: all clean fclean re
