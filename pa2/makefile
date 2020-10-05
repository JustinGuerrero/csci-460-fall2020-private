#b2bsim: b2bsim.o
#	gcc -pthread -o b2bsim b2bsim.o

#b2bsim.o: b2bsim.c
#	 gcc -W -Wall -ggdb -pthread b2bsim.c 

CC=gcc
CFLAGS=-W -Wall -std=c11 -ggdb -pthread
LIBS= -pthread 
SRCS= b2bsim.c
OBJS=$(SRCS:.c=.o)
TARGET= b2bsim

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -rf $(OBJS) $(TARGET) *~ # TODO: LIST ANY OTHER GENERATED FILES (WHICH SHOULD BE DELETED ON `make clean`) HERE - DELETE THIS COMMENT AFTER YOU'VE DONE THIS!
