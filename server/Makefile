SOURCE = serverside.c

OBJS = $(SOURCE:.cpp=.o)

LINK = gcc

main: $(OBJS)
	$(LINK) -o $@ $^

clean:
	rm -rf *.o *.d core main