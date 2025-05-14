CC = gcc
CFLAGS = -Wall -Iutils

# Inserisci qui librerie necessarie (es. -fopenmp per OpenMP)
ifeq ($(dir),openMP)
    CFLAGS += -fopenmp -IopenMP -DUSE_OPENMP
endif

ifeq ($(dir),prodotto_seriale)
    CFLAGS += -Iprodotto_seriale
endif

# Check se 'dir' è stato specificato
ifeq ($(dir),)
    $(error Devi specificare una directory con: make dir=prodotto_seriale oppure dir=openMP)
endif

# Sorgenti comuni
COMMON_SRC = utils/mmio.c utils/matrix_io.c utils/convert.c

# Sorgenti specifici della cartella selezionata
SRC = main.c $(COMMON_SRC) $(wildcard $(dir)/*.c)

# Genera i nomi dei file oggetto e dell'eseguibile
OBJ = $(SRC:.c=.o)
EXEC = matvec_exec

# Target predefinito
all: $(EXEC)

# Link dell'eseguibile
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

# Compilazione oggetti
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

#Clean
clean:
	rm -f $(OBJ) $(EXEC)

