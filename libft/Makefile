# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/26 08:29:35 by malja-fa          #+#    #+#              #
#    Updated: 2025/03/03 20:21:02 by taabu-fe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra
SRCS = ft_isascii.c ft_isprint.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
       ft_tolower.c ft_toupper.c ft_strlen.c ft_strlcpy.c ft_strlcat.c \
       ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c \
       ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_memchr.c \
       ft_memcmp.c ft_strdup.c ft_calloc.c ft_itoa.c ft_putchar_fd.c \
       ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_substr.c \
       ft_strjoin.c ft_strtrim.c ft_split.c ft_strmapi.c ft_striteri.c \
       ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c \
       ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c\
       ft_strtok.c ft_atoi_base.c ft_realloc.c ft_free_split.c ft_putchar.c\
       get_next_line.c get_next_line_utils.c ft_fprintf.c 

OBJECTS = $(SRCS:%.c=$(OBJDIR)/%.o)
NAME = libft.a
SRCDIR = src
OBJDIR=obj

all: $(NAME)


$(NAME): $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)
       
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -rf $(OBJDIR)


fclean: clean
	rm -f $(NAME)


re: fclean all

.PHONY: all clean fclean re
