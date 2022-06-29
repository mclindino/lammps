SRC = ./src
OBJ = ./obj
INCLUDE = ./include

all: obj_path
	mpicc -c $(SRC)/perf_status.c -I $(INCLUDE) -o $(OBJ)/perf_status.o

obj_path:
	mkdir -p $(OBJ)

clean:
	rm -rf $(OBJ)
