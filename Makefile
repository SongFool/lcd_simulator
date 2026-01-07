# =========================
# MCU LCD Simulator Makefile
# =========================

TARGET := lcd_sim.exe

CC := D:\Mingw\mingw\mingw64\bin\gcc.exe
#CC = E:/Mingw/x86_64-8.1.0-release-posix-seh-rt_v6-rev0/mingw64/bin/gcc.exe
CFLAGS := -Wall -O2 -std=c99 \
          -Iwin \
          -Ilcd \
          -Itty \
          -Ilib \
          -Igui

LDFLAGS := -lgdi32 -luser32

# -------- 目录设置 --------
OBJDIR := build/obj

# -------- 源文件 --------
SRCS := \
    main.c \
    win/win_lcd.c \
    win/win_key.c \
    lcd/lcd.c \
    gui/font.c \
    gui/gui.c \
    lib/fifo.c \
    tty/tty.c

# -------- 目标文件（统一到 OBJDIR）--------
OBJS := $(SRCS:%.c=$(OBJDIR)/%.o)

# 默认目标
all: $(TARGET)

# 链接
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

# 编译规则（自动创建子目录）
$(OBJDIR)/%.o: %.c
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CC) $(CFLAGS) -c $< -o $@

# 清理
clean:
	del /Q $(TARGET) 2>nul || true
	rmdir /S /Q build 2>nul || true

.PHONY: all clean
