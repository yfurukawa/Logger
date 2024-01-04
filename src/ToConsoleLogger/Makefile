RM = rm -f
CC = g++
INSTALL = install -m 644
INCLUUDE = -I/usr/include -I/usr/local/include
LD_PATH = -L/usr/lib64 -L/usr/local/lib64
LIB_DIR = /usr/local/lib64
LIB = 
OPT = -O0 -Wall -std=c++17 -fPIC -shared
TARGET = liblogger_Console.so.1.0.0
SRC = ToConsoleLoggerFactory.cpp ToConsoleLogger.cpp

$(TARGET): $(SRC:.cpp=.o)
	$(CC) $(INCLUUDE) $(LD_PATH) $(LIB) $(OPT) -o $(TARGET) $(SRC:.cpp=.o)

$(SRC:.cpp=.o):
	$(CC) $(INCLUUDE) $(LD_PATH) $(LIB) $(OPT) -c $(SRC)

.PHONY: clean install
clean:
	$(RM) *.o $(TARGET)

install:
	$(INSTALL) $(TARGET) $(LIB_DIR)
