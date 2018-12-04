#--------------------------------------------------
# Target file to be compiled by default
#--------------------------------------------------
MAIN = main
#--------------------------------------------------
# CC is the compiler to be used
#--------------------------------------------------
CC = gcc
#--------------------------------------------------
# CFLAGs are the options passed to the compiler
#--------------------------------------------------
CFLAGS = -Wall -lpthread -lrt -lm
#--------------------------------------------------
# OBJS are the objects files to be linked
#--------------------------------------------------
OBJ1 = tools
OBJS = $(MAIN).o $(OBJ1).o
#--------------------------------------------------
# LIBS are the external libraries to be used
#--------------------------------------------------
 # LIBS1= `allegro-config --libs
 LIBS2= `pkg-config allegro-5 allegro_font-5 allegro_image-5 allegro_primitives-5 --libs --cflags`
#--------------------------------------------------
# Dependencies
#--------------------------------------------------
$(MAIN): $(OBJS)
	$(CC) -o $(MAIN) $(OBJS) $(LIBS2)
# $(LIBS1) removed
$(MAIN).o: $(MAIN).c
	$(CC) -c $(MAIN).c

$(OBJ1).o: $(OBJ1).c
	$(CC) -c $(OBJ1).c

#--------------------------------------------------
# Command that can be specified inline: make clean
#--------------------------------------------------
clean:
	rm -rf *o $(MAIN) #--------------------------------------------------

# gcc -c main.c
# gcc -c tools.c
# gcc -o main main.o tools.o `pkg-config allegro-5 allegro_font-5 allegro_image-5 allegro_primitives-5 --libs --cflags`



# THIS PRODUCE:

# gcc -o main main.o tools.o  -Wall -lpthread -lrt -lm $(pkg-config allegro-5 allegro_font-5 allegro_image-5 allegro_primitives-5 --libs --cflags)
## gcc -o main main.o tools.o  -Wall -lpthread -lrt -lm $(pkg-config allegro-5 allegro_font-5 allegro_image-5 allegro_primitives-5 --libs --cflags)
##lanciare il secondo se voglio anche eseguire!
