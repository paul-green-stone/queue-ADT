cc = gcc
objs = temp/main.o temp/queue.o
dirs = temp
CFLAGS = -O1

main: $(objs) 
	$(cc) $(CFLAGS) -o a.out $(objs)

temp/main.o: main.c
	$(cc) -c -g -o temp/main.o main.c

temp/queue.o: queue.h queue.c
	$(cc) -c -g -o temp/queue.o queue.c

.PHONY: clean

clean:
	rm -rf temp ./*.o a.out 

$(shell mkdir -p $(dirs))