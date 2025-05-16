# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/16 13:21:34 by lbellmas          #+#    #+#              #
#    Updated: 2025/05/16 14:27:20 by lbellmas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME       = philo
BONUS		= philo_bonus
AR         = ar
ARFLAGS    = -rcs
CC         = cc
CFLAGS     = -Wall -Wextra -Werror -g -fsanitize=address
OFLAGS     = -MMD -MF $(@:.o=.d)

# Directorios
SRCDIR     = src
BSRCDIR		= bonus
UTILSDIR   = utils
DEPDIR     = deps
OBJDIR     = objs
BOBJDIR		= bonus_obj

# Archivos de cabecera
LIB        = header/ft_pipex.h

# Archivos fuente
SRC        =
BSRC		= 
UTILS      = ft_utils.c

# Archivos de objetos
OBJS       = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
BOBOJ		= $(addprefix $(BOBJDIR)/, $(BSRC:.c=.o))
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

$(BOBJ): $(BOBJDIR)/%.o : $(BSRCDIR)/%.c Makefile | $(BOBJDIR) $(DEPDIR)
	@printf "%-42b%b" "$(PURPLE)$<:" "$(BLUE)$(@F)$(RESET)\n"
	@$(CC) $(CFLAGS) $(OFLAGS) -c $< -o $@
	@mv $(OBJDIR)/*.d $(DEPDIR)

# Creación de directorios
$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(DEPDIR):
	@mkdir -p $(DEPDIR)

# Enlace final del ejecutable
$(NAME): $(MAIN) $(OBJS)
	@printf "%-42b%b" "$(PURPLE)$<:" "$(BLUE)$(@F)$(RESET)\n"
	@$(CC) $(CFLAGS) $(MAIN) $(OBJS) -o $(NAME)

bonus: $(BONUS) $(LIB) Makefile

$(BONUS): $(BMAIN) $(BOBJ)
	@printf "%-42b%b" "$(PURPLE)$<:" "$(BLUE)$(@F)$(RESET)\n"
	@$(CC) $(CFLAGS) $(BMAIN) $(BOBJ) -o $(BONUS)

# Limpiar objetos y dependencias
clean:
	@printf "%b" "$(BLUE)Cleaning objects...$(RESET)\n"
	@rm -rf $(OBJDIR)
	@rm -rf $(DEPDIR)

# Limpiar todo
fclean: clean
	@printf "%b" "$(BLUE)Cleaning all files...$(RESET)\n"
	@rm -f $(NAME)
	@rm -rf $(BONUS)

# Reconstrucción total
re: fclean all

.PHONY: all clean fclean re $(LIBPRINTF)
