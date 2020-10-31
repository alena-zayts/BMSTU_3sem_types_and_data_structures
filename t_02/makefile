CC := gcc
SRCS := app.c show_info.c inputs.c outputs.c deletes.c find.c sort.c compare.c
CFLAGS := -std=c99 -Wall -Werror -Wextra -Wfloat-equal -Wfloat-conversion -Wvla
OBJS := app.o show_info.o inputs.o outputs.o deletes.o find.o sort.o compare.o

#сборка основной программы
app.exe : $(OBJS)
	$(CC) $^ -o $@

#компоновка основных модулей
%.o : %.c
	$(CC) $(CFLAGS) -c $<
	
%.d : %.c
	$(CC) -M $< > $@

include $(SRCS:.c=.d)

.PHONY : clean 
clean :
	$(RM) *.o *.exe *.d
	
	
