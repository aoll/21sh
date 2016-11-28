#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/14 17:07:06 by aollivie          #+#    #+#              #
#    Updated: 2016/02/03 12:47:52 by aollivie         ###   ########.fr        #
#                                                                              #
#******************************************************************************#


DEBUG=yes
CC=clang

ifeq ($(DEBUG), yes)
				CFLAGS= -Wall -Wextra # -g -fsanitize=address,undefined # -g -ansi -pedantic
else
		CFLAGS= -Wall -Wextra -Werror
endif


NAME =project.exe

LIBFT =libft/libft.a

LIB_TEST_PROJECT= test_project/test_file/lib_test_project.a

LIB_UNIT_TEST=test_project/unit_test/lib_unit_test.a


LIB=-lncurses

I_DIR= -I inc/ -I./libft/inc -I./test_project/unit_test/inc -I./test_project/test_file/inc

O_DIR= obj

MKDIR = mkdir

C_SRC = main.c

C_TERM= ft_sup_char.c \
  			ft_move_up.c \
  			ft_move_down.c \
  			ft_move_left.c \
  			ft_move_right.c \
  			ft_move_x.c \
  			ft_cursor_save_position.c \
  			ft_cursor_restore_position.c \
  			ft_mode_reverse_video.c \
  			ft_mode_basic_video.c \
  			ft_mode_insertion.c \
  			ft_clear_down.c \
				my_putchar.c \
				ft_terminal_winsize.c

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
					ft_cursor_add_char.c

ST_SRC= ft_start.c ft_env_init.c ft_read_line.c

UC_SRC = main_test.c

ifeq ($(DEBUG), yes)
	MC_SRC = $(UC_SRC)
else
	MC_SRC = $(C_SRC)
endif

# VPATH= src
VPATH= src:test_project/test_file/src:src/terminal:src/cursor
# VPATH= src/str:src/put:src/int:src/mem:src/char:src/file:src/lst


OBJS= $(MC_SRC:%.c=$(O_DIR)/%.o) $(ST_SRC:%.c=$(O_DIR)/%.o) \
			$(C_TERM:%.c=$(O_DIR)/%.o) $(C_CURSOR:%.c=$(O_DIR)/%.o)



.PHONY : all clean fclean re

all :
	make -C libft
	make -C test_project/test_file
	make -j $(NAME)

ifeq ($(DEBUG),yes)
				@echo "Generation mode debug"
else
				@echo "Generation mode release"
endif

$(NAME):$(OBJS)
				$(CC)  $(CFLAGS) $(I_DIR) $^ $(LIB_TEST_PROJECT) $(LIB_UNIT_TEST) $(LIBFT) -o $@ $(LIB)


$(O_DIR)/%.o: %.c
				$(CC) $(CFLAGS) $(I_DIR) -c $< -o $@

$(OBJS): | $(O_DIR)

$(O_DIR):
				$(MKDIR) $(O_DIR)
clean :
		rm -rf $(O_DIR)
		make clean -C libft
		make clean -C test_project/test_file
		make clean -C test_project/unit_test

fclean : clean
		@rm -rf $(NAME)
		make fclean -C libft
		make fclean -C test_project/test_file
		make fclean -C test_project/unit_test

re : fclean all
