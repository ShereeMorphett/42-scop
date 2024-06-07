# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    MakeFile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/18 08:53:50 by smorphet          #+#    #+#              #
#    Updated: 2024/06/07 14:58:37 by smorphet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= scop

# directories
SRC_DIR	:= ./apps
LIB_DIR	:= ./libs
INC_DIR	:= ./include
OBJ_DIR	:= ./obj
BIN_DIR	:= ./bin

# src / obj files
SRC		:=	main.cpp

OBJ		:= $(addprefix $(OBJ_DIR)/,$(SRC:.cpp=.o))

# compiler
CC		:= c++
CFLAGS	:= -Wall -Wextra -Werror
CFLAGS	+= -O3 -march=native -pipe

# libraries
L_GLFW	:= $(LIB_DIR)/glfw-3.4

include $(LIB_DIR)/glfw.mk

# rules
all:
	cd $(L_GLFW) && cmake .
	@$(MAKE) -C $(L_GLFW) glfw --no-print-directory
	@$(MAKE) $(NAME) --no-print-directory
	@echo "[scop] 🎉"
	
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -I $(INC_DIR) $(LIB_INC) -o $@ -c $<

$(NAME): $(OBJ_DIR) $(OBJ)
	$(CC) $(OBJ) $(LIB_LNK) -o $(BIN_DIR)/$(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(BIN_DIR)/$(NAME)

re:
	@$(MAKE) fclean --no-print-directory
	@$(MAKE) all --no-print-directory

relibs:
	@$(MAKE) -C $(L_GLFW) clean --no-print-directory
	@$(MAKE) -C $(L_GLFW) glfw --no-print-directory
	@$(MAKE) fclean --no-print-directory
	@$(MAKE) all --no-print-directory

cleanlibs:
	@$(MAKE) -C $(L_GLFW) clean --no-print-directory

# special rules
.PHONY: all clean fclean re relibs