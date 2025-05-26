CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f 

SERVER = server 
CLIENT = client 

SRC_SERVER = server.c 
SRC_CLIENT = client.c 

OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

all: $(SERVER) $(CLIENT)
	@echo "server and client compiled, enjoy your chat."
	
$(SERVER): $(OBJ_SERVER)
	$(CC) $(CFLAGS) $(OBJ_SERVER) -o $(SERVER)

$(CLIENT): $(OBJ_CLIENT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) -o $(CLIENT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_SERVER) $(OBJ_CLIENT)

fclean: clean
	$(RM) $(SERVER) $(CLIENT)
	@echo "void got silent."

re: fclean all

.PHONY: all clean fclean re