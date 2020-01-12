CC = g++
SOURCE = pied.cpp
PROGRAM = pied
DEST = /usr/local/bin

$(PROGRAM): $(SOURCE)
	$(CC) $(SOURCE) `pkg-config opencv4 --cflags --libs` -o $(PROGRAM)

install: $(PROGRAM)
	install -s $(PROGRAM) $(DEST)