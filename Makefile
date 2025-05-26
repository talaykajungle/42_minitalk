# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

# Program names
SERVER = server
CLIENT = client

# Source and object files
SRC_UTILS = minitalk_utils.c
SRC_SERVER = server.c $(SRC_UTILS)
SRC_CLIENT = client.c $(SRC_UTILS)
OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

# Header file
HEADER = minitalk.h

# Default target
all: $(SERVER) $(CLIENT)
	@echo "\n Server and client compiled, enjoy your chat.\n"

# Link server executable
$(SERVER): $(OBJ_SERVER)
	$(CC) $(CFLAGS) $(OBJ_SERVER) -o $(SERVER)

# Link client executable
$(CLIENT): $(OBJ_CLIENT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) -o $(CLIENT)

# Compile source files to object files
%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	$(RM) $(OBJ_SERVER) $(OBJ_CLIENT)
	@echo "Object files removed."

# Clean object files and executables
fclean: clean
	$(RM) $(SERVER) $(CLIENT)
	@echo "Void got silent."

# Rebuild everything
re: fclean all

# Declare phony targets
.PHONY: all clean fclean re