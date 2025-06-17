# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/03 18:36:06 by jpelline          #+#    #+#              #
#    Updated: 2025/06/03 18:36:20 by jpelline         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============================== CONFIGURATION =============================== #

NAME		:= philo
CC		:= cc
CFLAGS		:= -Wextra -Wall -Werror
DEBUG_FLAGS	:= -g3 -fsanitize=address -fsanitize=undefined
OPTFLAGS	:= -O2

SRC_DIR		:= src

OBJ_DIR		:= obj

DEP_DIR		:= $(OBJ_DIR)/.deps
DEPFLAGS	= -MT $@ -MMD -MP -MF $(DEP_DIR)/$*.d

INC		:= -I./include

MARKER_STANDARD := .standard_build

# ============================== VISUAL STYLING ============================== #

BOLD		:= $(shell tput bold)
GREEN		:= $(shell tput setaf 2)
YELLOW		:= $(shell tput setaf 3)
BLUE		:= $(shell tput setaf 4)
MAGENTA		:= $(shell tput setaf 5)
CYAN		:= $(shell tput setaf 6)
WHITE		:= $(shell tput setaf 7)
RESET		:= $(shell tput sgr0)

# ============================== SOURCE FILES ================================ #

SRCS		:= main.c

# ============================== PROGRESS TRACKING =========================== #

OBJS		:= $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))
TOTAL_SRCS	:= $(words $(SRCS))

PROGRESS_FILE	:= $(OBJ_DIR)/.progress

LATEST_SRC	:= $(shell ls -t $(SRC_DIR)/*.c 2>/dev/null | head -n1)

OBJ_FILES_EXIST := $(shell [ -n "$(wildcard $(OBJ_DIR)/*.o)" ] && echo yes)

is_up_to_date = \
    [ -f $(NAME) ] && \
    [ "$(NAME)" -nt $(LATEST_SRC) ] && \
    [ "$(OBJ_FILES_EXIST)" = "yes" ]

# ============================== BUILD TARGETS =============================== #

all:
	@if [ -f $(MARKER_STANDARD) ] && $(is_up_to_date) 2>/dev/null; then \
		echo ">$(BOLD)$(YELLOW)  $(NAME) is already up to date.$(RESET)"; \
	else \
		echo ">$(BOLD)$(WHITE) Starting to build $(NAME)...$(RESET)"; \
		$(MAKE) $(NAME) --no-print-directory; \
		touch $(MARKER_STANDARD); \
		echo ">$(BOLD)$(GREEN)  All components built successfully!$(RESET)"; \
	fi

# Debug target
debug: CFLAGS += $(DEBUG_FLAGS)
debug: OPTFLAGS := -O0
debug: clean $(NAME)
	@echo "$(BOLD)$(CYAN)  Debug build completed!$(RESET)"

# Main executable target - links all objects and libraries
$(NAME): $(OBJS)
	@echo ">$(BOLD)$(GREEN)  Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(OPTFLAGS)
	@touch $(MARKER_STANDARD)
	@rm -f $(PROGRESS_FILE)
	@echo ">$(BOLD)$(GREEN)  $(NAME) successfully compiled!$(RESET)"

# Create necessary directories if they don't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "0" > $(PROGRESS_FILE)

$(DEP_DIR): | $(OBJ_DIR)
	@mkdir -p $@

# Compilation rule for each source file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR) $(DEP_DIR)
	@if [ -f $(PROGRESS_FILE) ]; then \
		CURRENT=$$(cat $(PROGRESS_FILE)); \
		NEXT=$$((CURRENT + 1)); \
		echo "$$NEXT" > $(PROGRESS_FILE); \
		printf ">   [%3d%%] $(CYAN)(%d/%d files) Compiling $<... $(RESET)\n" \
			$$((NEXT*100/$(TOTAL_SRCS))) $$((NEXT)) $(TOTAL_SRCS); \
	fi
	@$(CC) $(CFLAGS) $(DEPFLAGS) $(OPTFLAGS) -c $< -o $@ $(INC)

# Include auto-generated dependency files
-include $(wildcard $(DEP_DIR)/*.d)

# Remove object files and dependency files
clean:
	@if [ -d $(OBJ_DIR) ]; then \
		echo "> [ pipex ] $(YELLOW) Cleaning object files...$(RESET)"; \
		rm -rf $(OBJ_DIR); \
		echo "            $(YELLOW) Object files cleaned!$(RESET)"; \
	else \
		echo "> [ pipex ] $(BOLD)$(YELLOW) Nothing to be done with $(RESET)$(WHITE)clean$(RESET)"; \
	fi

# Remove everything including the executable
fclean: clean
	@if [ -f $(NAME) ]; then \
		echo "> [ pipex ] $(YELLOW) Removing $(NAME)...$(RESET)"; \
		rm -f $(NAME); \
		rm -f $(MARKER_STANDARD); \
		echo "            $(YELLOW) $(NAME) removed!$(RESET)"; \
	else \
		echo "> [ pipex ] $(BOLD)$(YELLOW) Nothing to be done with $(RESET)$(WHITE)fclean$(RESET)"; \
	fi

# Full rebuild from scratch
re:
	@echo "> [ pipex ] $(BOLD)$(WHITE) Rebuilding from scratch...$(RESET)"
	@$(MAKE) fclean --no-print-directory
	@$(MAKE) $(NAME) --no-print-directory

# Additional useful targets
help:
	@echo "$(BOLD)$(CYAN)Available targets:$(RESET)"
	@echo "  $(GREEN)all$(RESET)     - Build the project (default)"
	@echo "  $(GREEN)debug$(RESET)   - Build with debug flags and sanitizers"
	@echo "  $(GREEN)clean$(RESET)   - Remove object files"
	@echo "  $(GREEN)fclean$(RESET)  - Remove all generated files"
	@echo "  $(GREEN)re$(RESET)      - Rebuild from scratch"
	@echo "  $(GREEN)help$(RESET)    - Show this help message"

# Prevent intermediate files from being deleted
.SECONDARY: $(OBJS)
.PHONY: all debug clean fclean re help
