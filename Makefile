# ======================================================
# Makefile Documentation (краткая справка)
# ======================================================
#
# Переменные:
#   CC       - компилятор (gcc, clang)
#   CFLAGS   - флаги компиляции (-Wall, -O2 и т.д.)
#   LDFLAGS  - флаги линковки
#   LDLIBS   - подключаемые библиотеки (-lm)
#   TARGET   - имя исполняемого файла
#   SRCS     - исходные .c файлы (wildcard *.c)
#   OBJS     - объектные .o файлы (SRCS:.c=.o)
#   DEPS     - заголовочные .h файлы
#
# Функции:
#   $(addprefix <префикс>,<список>) - добавляет префикс к каждому элементу списка
#   $(SRCS:.c=.o)                   - заменяет .c на .o в списке файлов
#
# Автоматические переменные:
#   $@       - имя цели (target)
#   $<       - первая зависимость
#   $^       - все зависимости
#
# Основные цели (targets):
#   all      - сборка основной программы (по умолчанию)
#   clean    - удаление скомпилированных файлов
#   rebuild  - полная пересборка (clean + all)
#
# Шаблонные правила:
#   %.o: %.c - компиляция .c в .o
#
# Специальные директивы:
#   .PHONY   - цели, не связанные с файлами
#
# Пример использования:
#   make         - сборка программы
#   make clean   - очистка
#   make rebuild - полная пересборка
# ======================================================

CC := gcc
CFLAGS := -std=c11 -Wall -Werror -Wextra
BUILD_DIR := build
TARGET := run
TARGET_PATH := $(BUILD_DIR)/$(TARGET)
SRCS := sorting_algorithms.c
OBJS := $(addprefix $(BUILD_DIR)/,$(SRCS:.c=.o))

.PHONY: all clean rebuild

all: $(TARGET_PATH)

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET_PATH): $(OBJS) 
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR):
	mkdir -p $@

clean: 
	rm -rf $(BUILD_DIR)

rebuild: clean all