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


DEBUG=no
CC=clang

ifeq ($(DEBUG), yes)
				CFLAGS= -Wall -Wextra -g -ansi -pedantic
else
		CFLAGS= -Wall -Wextra
endif

LIB=ar rc
RANLIB=ranlib

AR = ar
ARFLAGS = rcs

NAME =lib_test_project.a

LIBFT = ../../libft/libft.a

LIB_UNIT_TEST=../unit_test/lib_unit_test.a

I_DIR= -I inc/ -I../../inc -I ../unit_test/inc -I../../libft/inc

O_DIR= obj

MKDIR = mkdir

VPATH= src


C_TEST_FILE= ut_print.c ut_env.c ut_free.c ut_arr.c ut_read_line.c

OBJS= $(C_TEST_FILE:%.c=$(O_DIR)/%.o)


.PHONY : all clean fclean re

all :
			make -C ../unit_test
			make -j $(NAME)


ifeq ($(DEBUG),yes)
				@echo "Generation mode debug"
else
				@echo "Generation mode release"
endif

$(NAME):$(OBJS) $(LIBFT) $(LIB_UNIT_TEST)
				$(AR) $(ARFLAGS) $@ $^


# %.o: libft.h -I

$(O_DIR)/%.o: %.c
				$(CC) $(CFLAGS) $(I_DIR) -o $@ -c $<

$(OBJS): | $(O_DIR)

$(O_DIR):
				$(MKDIR) $(O_DIR)
clean :
		rm -rf $(O_DIR)

fclean : clean
		@rm -rf $(NAME)

re : fclean all
