# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic -Iinclude
DEBUG_CFLAGS = -g -O0
RELEASE_CFLAGS = -O2

# Директории
SRC_DIR = src
INCLUDE_DIR = include
TEST_DIR = test
LIB_DIR = lib
OBJ_DIR = obj

# Цели сборки
TARGET = $(TEST_DIR)/run
LIBRARY = $(LIB_DIR)/libpermutations.a

# Исходные файлы
SRCS = $(wildcard $(SRC_DIR)/*.c)
TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)

# Объектные файлы
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TEST_OBJS = $(filter-out $(OBJ_DIR)/main.o, $(OBJS)) \
            $(TEST_SRCS:$(TEST_DIR)/%.c=$(OBJ_DIR)/%.o)

# Основная цель по умолчанию
all: debug

# Отладочная сборка
debug: CFLAGS += $(DEBUG_CFLAGS)
debug: $(TARGET)

# Релизная сборка
release: CFLAGS += $(RELEASE_CFLAGS)
release: $(TARGET)

# Сборка библиотеки
library: CFLAGS += $(RELEASE_CFLAGS)
library: $(LIBRARY)

# Исполняемый файл тестов
$(TARGET): $(TEST_OBJS) | $(LIB_DIR)
	$(CC) $(CFLAGS) -o $@ $(TEST_OBJS)

# Статическая библиотека
$(LIBRARY): $(OBJS) | $(LIB_DIR)
	ar rcs $@ $(OBJS)

# Компиляция объектных файлов для исходного кода
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Компиляция объектных файлов для тестов
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Создание необходимых директорий
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

# Очистка
clean:
	rm -rf $(OBJ_DIR) $(LIB_DIR) $(TARGET)

# Пересборка
rebuild: clean all

# Запуск тестов
test: debug
	./$(TARGET)

# Вспомогательные цели
.PHONY: all debug release library clean rebuild test

# Зависимости для main.o (если будет отдельный main)
$(OBJ_DIR)/main.o: $(INCLUDE_DIR)/permutations.h

# Зависимости для тестов
$(OBJ_DIR)/test.o: $(INCLUDE_DIR)/permutations.h
