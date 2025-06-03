# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/16 13:21:34 by lbellmas          #+#    #+#              #
#    Updated: 2025/06/03 14:44:11 by lbellmas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME       = philo
AR         = ar
ARFLAGS    = -rcs
CC         = cc
CFLAGS     = -Wall -Wextra -Werror -g #-fsanitize=thread
OFLAGS     = -MMD -MF $(@:.o=.d)

# Directorios
SRCDIR     = src
UTILSDIR   = ../utils
DEPDIR     = deps
OBJDIR     = objs
OUTILSDIR	= utils_objects

# Archivos de cabecera
LIB        = header.h

# Archivos fuente
SRC        = ft_loop.c ft_eat.c
UTILS      = ft_utils.c

# Archivos de objetos
OBJS       = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
OUTILS	= $(addprefix $(OUTILSDIR)/, $(UTILS:.c=.o))
DEPS       = $(addprefix $(DEPDIR)/, $(SRC:.c=.d) $(UTILS:.c=.d) $(GET:.c=.d))

# Archivo principal
MAIN       = ft_philo.c
BMAIN		=
# Colores
RED        = \033[0;31m
GREEN      = \033[0;32m
YELLOW     = \033[0;33m
BLUE       = \033[0;34m
PURPLE     = \033[0;35m
CYAN       = \033[0;36m
RESET      = \033[m

# Objetivo principal
all: $(NAME) $(LIB) Makefile

-include $(DEPS)

# Compilación de archivos fuente generales
$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.c Makefile | $(OBJDIR) $(DEPDIR)
	@printf "%-42b%b" "$(PURPLE)$<:" "$(BLUE)$(@F)$(RESET)\n"
	@$(CC) $(CFLAGS) $(OFLAGS) -c $< -o $@
	@mv $(OBJDIR)/*.d $(DEPDIR)

$(OUTILS): $(OUTILSDIR)/%.o : $(UTILSDIR)/%.c Makefile | $(OUTILSDIR) $(DEPDIR)
	@printf "%-42b%b" "$(PURPLE)$<:" "$(BLUE)$(@F)$(RESET)\n"
	@$(CC) $(CFLAGS) $(OFLAGS) -c $< -o $@
	@mv $(OUTILSDIR)/*.d deps/

# Creación de directorios
$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(DEPDIR):
	@mkdir -p $(DEPDIR)

$(OUTILSDIR):
	@mkdir -p $(OUTILSDIR)

# Enlace final del ejecutable
$(NAME): $(MAIN) $(OBJS) $(OUTILS)
	@printf "%-42b%b" "$(PURPLE)$<:" "$(BLUE)$(@F)$(RESET)\n"
	@$(CC) $(CFLAGS) $(MAIN) $(OBJS) $(OUTILS) -o $(NAME)

# Limpiar objetos y dependencias
clean:
	@printf "%b" "$(BLUE)Cleaning objects...$(RESET)\n"
	@rm -rf $(OBJDIR)
	@rm -rf $(DEPDIR)
	@rm -rf $(OUTILSDIR)

# Limpiar todo
fclean: clean
	@printf "%b" "$(BLUE)Cleaning all files...$(RESET)\n"
	@rm -f $(NAME)

# Reconstrucción total
re: fclean all

.PHONY: all clean fclean re
