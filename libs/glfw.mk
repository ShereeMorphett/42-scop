L_GLFW		?= ./glfw-3.4

GLFW_NAME	:= OpenGL.a

GLFW_INC    := -I $(L_GLFW)/include

ifeq ($(shell uname),Darwin)
    GLFW_LNK    := -L $(L_GLFW)/src -l glfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
else
    GLFW_LNK    := -L $(L_GLFW)/src -l glfw3
endif


GLFW_INC	:= -I $(L_GLFW)/include
GLFW_LIB	:= $(L_FT)/$(FT_NAME)

# Global variables for compilation
ifndef LIB_LNK
LIB_LNK		:=
LIB_INC		:=
endif

LIB_LNK		+= $(GLFW_LNK)
LIB_INC		+= $(GLFW_INC)