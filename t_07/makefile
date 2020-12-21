app.exe : 
	gcc -std=c99 -Wall -Wextra -Wfloat-equal -Wfloat-conversion -Wvla -c main.c adj_matrix.c graph.c cut.c welcome.c tick.c
	gcc -o app.exe main.o adj_matrix.o graph.o cut.o welcome.o tick.o
	
.PHONY : clean 
clean :
	rm *.o *.exe 