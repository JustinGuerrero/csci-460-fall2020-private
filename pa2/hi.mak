CC=gcc
CFLAGS=-W -Wall -std=c11 -ggdb 
LIBS= -pthread -m32
SRCS= b2bsim.c
OBJS=$(SRCS:.c=.o) 
TARGET= # b2bsim


.PHONY: run
run: b2bsim.c
		$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS) $(OBJS) 




.PHONY: clean
clean:
	rm -rf $(OBJS) $(TARGET) *~ # TODO: LIST ANY OTHER GENERATED FILES (WHICH SHOULD BE DELETED ON `make clean`) HERE - DELETE THIS COMMENT AFTER YOU'VE DONE THIS!

