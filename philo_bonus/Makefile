# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/03 14:26:48 by lbellmas          #+#    #+#              #
#    Updated: 2025/06/09 14:00:41 by lbellmas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BONUS		= philo_bonus
AR         = ar
ARFLAGS    = -rcs
CC         = cc
CFLAGS     = -Wall -Wextra -Werror -g #-fsanitize=address
OFLAGS     = -MMD -MF $(@:.o=.d)

# Directorios
BSRCDIR		= bonus
UTILSDIR   = ../utils
DEPDIR     = deps
BOBJDIR		= bonus_obj
OUTILSDIR	= utils_objects

# Archivos de cabecera
LIB        = header_bonus.h

# Archivos fuente
BSRC		= ft_eat.c ft_loop.c ft_assignments.c
UTILS      = ft_utils.c

# Archivos de objetos
OBJS       = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
BOBJ		= $(addprefix $(BOBJDIR)/, $(BSRC:.c=.o))
OUTILS	= $(addprefix $(OUTILSDIR)/, $(UTILS:.c=.o))
DEPS       = $(addprefix $(DEPDIR)/, $(SRC:.c=.d) $(UTILS:.c=.d) $(GET:.c=.d))

# Archivo principal
BMAIN		= ft_philo_bonus.c
# Colores
RED        = \033[0;31m
GREEN      = \033[0;32m
YELLOW     = \033[0;33m
BLUE       = \033[0;34m
PURPLE     = \033[0;35m
CYAN       = \033[0;36m
RESET      = \033[m
all:
	@printf "make *** No rule no make target''.\n"
-include $(DEPS)

# Compilación de archivos fuente generales
$(BOBJ): $(BOBJDIR)/%.o : $(BSRCDIR)/%.c Makefile | $(BOBJDIR) $(DEPDIR)
	@printf "%-42b%b" "$(PURPLE)$<:" "$(BLUE)$(@F)$(RESET)\n"
	@$(CC) $(CFLAGS) $(OFLAGS) -c $< -o $@
	@mv $(BOBJDIR)/*.d deps/

$(OUTILS): $(OUTILSDIR)/%.o : $(UTILSDIR)/%.c Makefile | $(OUTILSDIR) $(DEPDIR)
	@printf "%-42b%b" "$(PURPLE)$<:" "$(BLUE)$(@F)$(RESET)\n"
	@$(CC) $(CFLAGS) $(OFLAGS) -c $< -o $@
	@mv $(OUTILSDIR)/*.d deps/

# Creación de directorios
$(BOBJDIR):
	@mkdir -p $(BOBJDIR)

$(DEPDIR):
	@mkdir -p $(DEPDIR)

$(OUTILSDIR):
	@mkdir -p $(OUTILSDIR)

bonus: $(BONUS) $(LIB) Makefile

$(BONUS): $(BMAIN) $(BOBJ) $(OUTILS)
	@printf "%-42b%b" "$(PURPLE)$<:" "$(BLUE)$(@F)$(RESET)\n"
	@$(CC) $(CFLAGS) $(BMAIN) $(BOBJ) $(OUTILS) -o $(BONUS)

# Limpiar objetos y dependencias
clean:
	@printf "%b" "$(BLUE)Cleaning objects...$(RESET)\n"
	@rm -rf $(BOBJDIR)
	@rm -rf $(DEPDIR)
	@rm -rf $(OUTILSDIR)

# Limpiar todo
fclean: clean
	@printf "%b" "$(BLUE)Cleaning all files...$(RESET)\n"
	@rm -f $(NAME)
	@rm -rf $(BONUS)

# Reconstrucción total
re: fclean bonus

.PHONY: all clean fclean re
