TARGET2 = TCP_IP_klient
TARGET = TCP_IP_server

CC = gcc

CFLAGS += -Wall -Wextra -Werror 

LIBS += 


BILD_DIR = obj/

SRC_DIR = src/
INCLUDE_DIR += -I$(SRC_DIR)debug

CFILES += $(SRC_DIR)TCP_SRV/tcp_srv.c

CFILES+= $(SRC_DIR)main.c


CFILES2+=$(SRC_DIR)klient.c
CFILES2 += $(SRC_DIR)TCP_SRV/tcp_srv.c

all:
	mkdir -p obj
	$(CC) $(CFILES) $(INCLUDE_DIR) $(LIBS) -o  $(BILD_DIR)$(TARGET) $(CFLAGS) 
	$(CC) $(CFILES2) $(INCLUDE_DIR) $(LIBS) -o $(BILD_DIR)$(TARGET2) $(CFLAGS) 

clean_dir:
	rm -Rf $(BILD_DIR)

clean:clean_dir