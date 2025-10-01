# Компилятор и флаги
CC = gcc
# Включаем отладочную информацию и информацию для покрытия кода
CFLAGS = -std=c99 -Wall -Wextra -g --coverage
# Линковщик и его флаги
LDFLAGS = --coverage

# Исходные файлы
SRCS = permutation.c main.c
OBJS = $(SRCS:.c=.o)

# Исходники тестов
TEST_SRCS = permutation.c test.c
TEST_OBJS = $(TEST_SRCS:.c=.o)

# Имена исполняемых файлов
TARGET = permutation_app
TEST_TARGET = run_tests

# Цель по умолчанию - собрать основную программу
all: $(TARGET)

$(TARGET): $(OBJS)
 $(CC) $(LDFLAGS) -o $@ $^

$(TEST_TARGET): $(TEST_OBJS)
 $(CC) $(LDFLAGS) -o $@ $^

# Правило для сборки .o файлов
%.o: %.c permutation.h
 $(CC) $(CFLAGS) -c $< -o $@

# Запустить тесты
test: $(TEST_TARGET)
 ./$(TEST_TARGET)

# Посчитать покрытие кода тестами
coverage: test
 # Генерируем отчет по покрытию
 gcov -b -c $(TEST_SRCS)
 # Показываем удобный отчет в консоли (нужна утилита lcov)
 # Сначала генерируем .info файл
 lcov --capture --directory . --output-file coverage.info
 # Затем выводим отчет в консоль
 lcov --list coverage.info
 # Для генерации HTML отчета можно использовать:
 # genhtml coverage.info --output-directory coverage_report

# Очистка
clean:
 rm -f $(TARGET) $(TEST_TARGET) *.o *.gcno *.gcda *.gcov *.info
 rm -rf coverage_report

.PHONY: all test coverage clean
