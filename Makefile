# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/14 17:07:06 by aollivie          #+#    #+#              #
#    Updated: 2017/05/21 19:07:42 by alex             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


DEBUG=yes
CC=clang

ifeq ($(DEBUG), yes)
				CFLAGS= -Wall -Wextra -Wno-unused-variable -Wno-unused-parameter -O1 -g #-fsanitize=address -fno-omit-frame-pointer # -g -fsanitize=address,undefined # -g -ansi -pedantic
else
		CFLAGS= -Wall -Wextra -Werror #-O1 -g #-fsanitize=address -fno-omit-frame-pointer
endif


NAME =minishell

LIBFT =libft/libft.a

LIB_TEST_PROJECT=

LIB_UNIT_TEST=


LIB=-lncurses

I_DIR= -I inc/ -I./libft/inc

O_DIR= obj

MKDIR = mkdir

C_SRC = main.c

C_TERM= ft_sup_char.c \
  			ft_move_up.c \
  			ft_move_down.c \
  			ft_move_left.c \
  			ft_move_right.c \
  			ft_move_x.c \
  			ft_mode_reverse_video.c \
  			ft_mode_basic_video.c \
  			ft_mode_insertion.c \
			my_putchar.c \
			ft_terminal_winsize.c \
			ft_terminal_tool.c

C_READ= ft_read_parse.c \
				ft_read_ctrl_c_env.c \
				ft_read_parse_actions.c \
				ft_read_parse_eof.c \
				ft_read_stdin.c \
				ft_init_list_arr.c \
				ft_check_loop.c \
				ft_init_init_term_arr.c \
				ft_read_deselect.c \
				ft_read_exit.c \
				ft_read_exec.c \
				ft_read_get.c \
				ft_read_end.c \
				ft_read_no_env.c \
				ft_read_env.c \
				ft_read_line.c \
				ft_env_init.c

C_CURSOR= ft_cursor_left.c \
					ft_cursor_right.c \
					ft_cursor_home.c \
					ft_cursor_end.c \
					ft_cursor_del_or_suppr.c \
					ft_cursor_move_to_start.c \
					ft_restore_prompt_and_line.c \
					ft_cursor_move_to_index_line_from_start.c \
					ft_cursor_word_left.c \
					ft_cursor_word_right.c \
					ft_cursor_select_left.c \
					ft_cursor_select_right.c \
					ft_cursor_deselect_all.c \
					ft_cursor_add_char.c \
					ft_cursor_resize.c \
					ft_cursor_copy_line.c \
					ft_cursor_cut.c \
					ft_cursor_paste.c \
					ft_cursor_up_line.c \
					ft_cursor_down_line.c \
					ft_cursor_up_history_line.c \
					ft_cursor_down_history_line.c \
					ft_cursor_valide_line.c \
					ft_cursor_valide_line_init_cursor_prompt.c \
					ft_cursor_valide_line_with_line.c \
					ft_cursor_valide_line_without_line.c \
					ft_cursor_clear_up.c \
					ft_cursor_clear_down.c \
					ft_arr_add_char.c \
					ft_arr_index_line_start_showed.c \
					ft_cursor_print_char.c \
					ft_cursor_print_chariot.c \
					ft_cursor_print_overide_line.c \
					ft_cusor_clear_down_line.c \
					ft_cursor_left_tab.c \
					ft_cursor_left_same_line.c \
					ft_nb_char_between_two_chariot.c \
					ft_cursor_left_chariot.c \
					ft_cursor_index_prev_line_end.c \
					ft_cursor_nb_line_displayed.c \
					ft_cursor_restore_y_x.c \
					ft_cursor_right_tab.c \
					ft_cursor_right_chariot.c \
					ft_cursor_right_same_line.c \
					ft_clear_up_from_bottom.c \
					ft_index_line_end_showed.c \
					ft_index_line_start_showed.c \
					ft_cursor_right_line_more.c \
					ft_cursor_right_line_more_up.c \
					ft_cursor_y_screen.c \
					ft_cursor_select_overide_tab.c \
					ft_cursor_select_overide_char.c \
					ft_init_cursor_cmd.c \
					ft_free_cursor.c \
					ft_init_cursor_position.c \
					ft_arr_del_char_check_quote_is_inside.c

C_PARSE= ft_parse_line.c \
				 ft_parse_separate_cmd.c \
				 ft_parse_init_cmd_line.c \
				 ft_parse_init_new_arr_line.c \
				 ft_parse_check_d_quote.c \
				 ft_parse_pop_space_inside.c \
				 ft_parse_pop_prev_space.c \
				 ft_parse_replace_space.c \
				 ft_parse_replace_d_left_redirect.c \
				 ft_parse_replace_d_right_redirect.c \
				 ft_parse_replace_s_right_redirect.c \
				 ft_parse_replace_s_left_redirect.c \
				 ft_parse_replace_pipe.c \
				 ft_parse_replace_file_redirect.c \
				 ft_parse_check_double_redirect.c \
				 ft_parse_replace_stdin_sdterr_redirect.c \
				 ft_parse_replace_sdterr_redirect.c \
				 ft_parse_replace_stderr_prev_line.c \
				 ft_parse_replace_sdterr_double_redirect.c \
				 ft_parse_replace_stderr_double_prev_line.c \
				 ft_parse_check_double.c \
				 ft_parse_is_only_space.c \
				 ft_parse_check_end_space.c \
				 ft_parse_check_file_redirect.c \
				 ft_parse_check_error.c \
				 ft_parse_pop_and_replace_and_check_error.c \
				 ft_check_is_char.c

C_BUILTIN= ft_is_builtin.c \
					 ft_builtin_exec.c \
					 ft_builtin_env.c \
					 ft_builtin_setenv.c \
					 ft_builtin_unsetenv.c \
					 ft_builtin_echo.c \
					 ft_builtin_cd.c \
					 ft_builtin_exit.c \
					 ft_builtin_setenv_check_argument.c \
					 ft_builtin_cd_set_env.c \
					 ft_builtin_cd_absolute_path.c \
					 ft_builtin_cd_is_existing_file.c \
					 ft_builtin_cd_change_directory.c \
					 ft_builtin_env_print.c \
					 ft_builtin_env_setenv.c \
					 ft_builtin_env_set_var_is_cmd.c \
					 ft_builtin_env_free_kval.c \
					 ft_builtin_env_set_var_cmd.c \
					 ft_free_name_value.c

C_FORK= ft_fork_name_file.c \
				ft_fork_env_arr_to_tab_str.c \
				ft_fork_fd.c \
				ft_fork_list_fd.c \
				ft_fork_list_fd_null.c \
				ft_fork_fd_from_name.c \
				ft_fork_list_fd_dup.c \
				ft_fork_list_fd_stderr.c \
				ft_fork_list_fd_left_redirect.c \
				ft_fork_list_fd_tmp.c \
				ft_arr_close_arr_fd.c \
				ft_fork_write_list_fd.c \
				ft_fork_list_d_end_word.c \
				ft_arr_free_arr_fd.c \
				ft_fork_init_arr_fd.c \
				ft_fork_close_array_tube.c \
				ft_fork_pipe_array_tube.c \
				ft_fork_set_tube.c \
				ft_fork_is_error_ptr.c \
				ft_fork_init_path.c \
				ft_fork_command_not_found.c \
				ft_fork_write_tube_stdin.c \
				ft_fork_read_stdin_file.c \
				ft_fork_write_tube.c \
				ft_fork_write_fd_stdout.c \
				ft_fork_write_fd_stderr.c \
				ft_fork_open_file.c \
				ft_fork_init_loop.c \
				ft_fork_set_tube_fd.c \
				ft_fork_check_is_builtin_exit.c \
				ft_fork_pid_son.c \
				ft_fork_is_stdin_fd.c \
				ft_fork_set_tube_father.c \
				ft_fork_father.c \
				ft_fork_create_process.c \
				ft_fork_init_st_fork.c \
				ft_fork_back_std.c \
				ft_fork_free_st_fork_and_arr_fd.c \
				ft_fork_init_tab_cmd.c \
				ft_fork_init_env_copy.c \
				ft_fork_set_env_copy.c \
				ft_fork.c \
				ft_fork_son_exec.c \
				ft_fork_nb_pipe.c \
				ft_fork_str_from_arr.c \
				ft_fork_split_pipe.c \
				ft_fork_loop.c

C_SIGNAL= ft_signal_init.c \
					ft_signal_restore.c

ST_SRC=


UC_SRC = main_test.c

MC_SRC = $(C_SRC)
#disabled
# ifeq ($(DEBUG), yes)
# 	MC_SRC = $(UC_SRC)
# else
# 	MC_SRC = $(C_SRC)
# endif

# VPATH= src
VPATH= src:src/terminal:src/cursor:src/parse:src/builtin:src/read:src/fork:src/signal



OBJS= $(MC_SRC:%.c=$(O_DIR)/%.o) $(ST_SRC:%.c=$(O_DIR)/%.o) \
			$(C_TERM:%.c=$(O_DIR)/%.o) $(C_CURSOR:%.c=$(O_DIR)/%.o) \
			$(C_PARSE:%.c=$(O_DIR)/%.o) $(C_BUILTIN:%.c=$(O_DIR)/%.o) \
			$(C_READ:%.c=$(O_DIR)/%.o) $(C_FORK:%.c=$(O_DIR)/%.o) \
			$(C_SIGNAL:%.c=$(O_DIR)/%.o)



.PHONY : all clean fclean re

all :
	make -C libft
	make -j $(NAME)

ifeq ($(DEBUG),yes)
				@echo "Generation mode debug"
else
				@echo "Generation mode release"
endif

$(NAME):$(OBJS)
				$(CC)  $(CFLAGS) $(I_DIR) $^  $(LIBFT) -o $@ $(LIB)


$(O_DIR)/%.o: %.c
				$(CC) $(CFLAGS) $(I_DIR) -c $< -o $@

$(OBJS): | $(O_DIR)

$(O_DIR):
				$(MKDIR) $(O_DIR)
clean :
		rm -rf $(O_DIR)
		make clean -C libft

fclean : clean
		@rm -rf $(NAME)
		make fclean -C libft

re : fclean all
