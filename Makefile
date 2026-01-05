# =========================
# MCU LCD Simulator Makefile
# =========================

TARGET  := lcd_sim.exe

CC = E:/Mingw/x86_64-8.1.0-release-posix-seh-rt_v6-rev0/mingw64/bin/gcc.exe
CFLAGS  := -Wall -O2 -std=c99 \
			-Iwin \
			-Ilcd
LDFLAGS := -lgdi32 -luser32

SRCS := \
    main.c \
    win/win_lcd.c \
    lcd/lcd.c

OBJS := $(SRCS:.c=.o)

# 默认目标
all: $(TARGET)

# 链接
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

# 编译（支持子目录）
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理（递归删除）
clean:
	del /Q *.exe 2>nul || true
	del /Q win\*.o 2>nul || true
	del /Q lcd\*.o 2>nul || true

.PHONY: all clean
