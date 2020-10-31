CC := gcc
SRCS := app.c free_array.c show_info.c stack_array.c stack_list.c stack_operations.c tick.c
CFLAGS := -std=c99 -Wall -Werror -Wextra -Wfloat-equal -Wfloat-conversion -Wvla
OBJS := app.o free_array.o show_info.o stack_array.o stack_list.o stack_operations.o tick.o

#сборка основной программы
app.exe : $(OBJS)
	$(CC) $^ -o $@

#компоновка основных модулей
%.o : %.c
	$(CC) $(CFLAGS) -c $<
	
%.d : %.c
	$(CC) -M $< > $@

.PHONY : clean 
clean :
	$(RM) *.o *.exe *.d
	
	
