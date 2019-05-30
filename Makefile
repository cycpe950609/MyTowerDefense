
CC = g++
CFLAG = -Wall -std=c++11
TARGET = game.out
SOURCEFILE = *.cpp
OBJFILE = *.o
ALLEGRO = `pkg-config --libs allegro-5 allegro_font-5 allegro_ttf-5 allegro_dialog-5 allegro_primitives-5 allegro_image-5 allegro_audio-5 allegro_acodec-5`

LIB = -Iallegro

all: 
	$(CC) -c -g $(CFLAG) $(SOURCEFILE)
	$(CC) $(OBJFILE) -o $(TARGET) $(ALLEGRO) $(LIB) 
	./$(TARGET)

compile: 
	$(CC) -c -g $(CFLAG) $(SOURCEFILE)
linker:
	$(CC) $(OBJFILE) -o $(TARGET) $(ALLEGRO) $(LIB)

fuck:
	$(CC) $(CFLAG) -o $(TARGET) $(LIB) $(SOURCEFILE) $(ALLEGRO) 
clean:
	rm *.o
