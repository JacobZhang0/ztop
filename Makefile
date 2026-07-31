CC = clang
CFLAGS = -Wall -Wextra -Wpedantic -g -O0
TARGET = src/main
OBJS = src/main.o src/cpu.o src/memory.o src/process.o 

$(TARGET): $(OBJS)
	$(CC) $^ -o $(TARGET)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: cleano clean
cleano: 
	rm -f $(OBJS)
clean:
	rm -f rm -f $(OBJS) $(TARGET)
