CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb
TARGET = dressed.txt
SRC = $(TARGET).txt
OBJ = $(TARGET).o
#TOZIPDIRS = $(filter %/, $(wildcard subdir))
#TOZIPNAMES = $(patsubst %/ , %, $(TOZIPDIRS))
#ZIPTARGETS = $(addsuffix .zip, $(TOZIPNAMES))

zip: 
	tar -zcvf dressedUP.tar.gz task5

debug: 
	@echo $(TOZIPDIRS)
	@echo $(TOZIPNAMES)
	@echo $(ZIPTARGETS)

#.PHONY: clean
#$(TARGET): $(OBJS)
#	$(CC) $(CFLAGS) $(SRC) -o $@ 2>/dev/null;zip -j $@ $^


#clean:
#	$(RM) $(TARGET) $(OBJS)
