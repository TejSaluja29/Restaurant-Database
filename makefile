CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

TARGET = bin/snackaroo.exe
HEADERS = include/snackaroo.h include/snackaroo_dish.h include/snackaroo_driver.h include/snackaroo_relationship.h
OBJECTS = build/snackaroo.o build/snackaroo_dish.o build/snackaroo_driver.o build/snackaroo_relationship.o

.PHONY: all clean rebuild

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

build/%.o: src/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	powershell -NoProfile -Command "Remove-Item -LiteralPath 'build\\snackaroo.o','build\\snackaroo_dish.o','build\\snackaroo_driver.o','build\\snackaroo_relationship.o','bin\\snackaroo.exe' -Force -ErrorAction SilentlyContinue"

rebuild: clean all
