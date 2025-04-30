CC = gcc
CFLAGS = -Wall -Iutils -Iprodotto_seriale

SRC = main.c \
      utils/mmio.c \
      utils/matrix_io.c \
      utils/convert.c \
      prodotto_seriale/matvec_serial.c

OBJ = $(SRC:.c=.o)
EXEC = matvec_serial

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

