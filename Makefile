OBJ = my_mastermind.o
TARGET = my_mastermind
CC = gcc
SRC = mastermind.c

.PHONY : all clean fclean re

all : $(TARGET)

$(TARGET) : $(OBJ)
	$(CC) -o $@ $^  

.c.o :
	$(CC) -c $^

clean : 
	rm -f *.o 

fclean : clean 
	rm -f $(TARGET)
	
re : fclean all