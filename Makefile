TARGET = ProgManag
TARGET2 = find_proces
CC = gcc

CFLAGS += -Wall -Wextra -Werror 

LIBS += -pthread


BILD_DIR = obj/

SRC_DIR = src/

CFILES += $(SRC_DIR)main.c
CFILES += $(SRC_DIR)utils/find.c

CFILES_F += $(SRC_DIR)utils/find_process/find_process.c

INCLUDE += -Isrc/include

all:
	mkdir -p obj
	$(CC)  $(LIBS) $(INCLUDE) $(CFILES) -o $(BILD_DIR)$(TARGET) $(CFLAGS) 
	$(CC)  $(LIBS) $(INCLUDE) $(CFILES_F) -o $(BILD_DIR)$(TARGET2) $(CFLAGS) 


clean_dir:
	rm -Rf $(BILD_DIR)

clean:clean_dir