# credit: https://endler.dev/2017/makefiles/

# 	target: [dependencies]
#	example.o:example.c .PHONY 
# 	<shell command to execute>
CC = gcc
CFLGAGS = iWall -pedantic -std=c11 -ggdb
TARGET = dressed.txt
SRC = $(TARGET).txt
OBJ = $(TARGET).zip

dress: trousers shoes jacket 
	@echo "All done. Let's go outside!" >> dressed.txt

jacket: pullover
	@echo "Putting on jacket." >> dressed.txt

pullover: shirt
	@echo "Putting on pullover." >> dressed.txt

shirt:
	@echo "Putting on shirt." >> dressed.txt

trousers: underpants
	@echo "Putting on trousers." >> dressed.txt

underpants:
	@echo "Putting on underpants." >> dressed.txt

shoes: socks
	@echo "Putting on shoes." >> dressed.txt

socks: pullover
	@echo "Putting on socks." >> dressed.txt


.PHONY: clean
$(TARGET): $(OBJS)
	$(CC) $(CLFLAGS) $(SRC) -O $@
	hdressed: dressed.zip
	gcc -Wall -pedantic -std=c11 -ggdb -dressed.txt -o dressed.zip



clean: dressed.txt
	$(RM) $(TARGET) $(OBJS)
