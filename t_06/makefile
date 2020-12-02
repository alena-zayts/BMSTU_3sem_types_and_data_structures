CC := gcc
SRCS := $(wildcard *.c)
OBJS := $(SRCS:%.c=%.o)
CFLAGS := -Wall -Werror -pedantic -Wextra -Wvla -std=c99

app.exe: $(OBJS) *.h
        $(CC) $(CFLAGS) $(OBJS) -o app.exe

%.o: %.c *.h
        $(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
        $(RM) *.o *.exe
