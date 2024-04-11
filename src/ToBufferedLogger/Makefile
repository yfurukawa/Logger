RM = rm -f
CC = g++
INSTALL = install -m 644
INCLUUDE = -I/usr/include -I/usr/local/include
LD_PATH = -L/usr/lib64 -L/usr/local/lib64
LIB_DIR = /usr/local/lib64
LIB = /usr/local/lib64/libfileinterface.a /usr/local/lib64/libclock.a
OPT = -O0 -Wall -std=c++17 -fPIC -shared -pthread

TARGET = liblogger_BufferedFile.so.1.1.0
SRC = ToBufferedLoggerFactory.cpp ToBufferedLogger.cpp ContentBuffer.cpp

$(TARGET): $(SRC:.cpp=.o)
	$(CC) $(INCLUUDE) $(LD_PATH) $(OPT) -o $(TARGET) $(SRC:.cpp=.o) $(LIB)

$(SRC:.cpp=.o):
	$(CC) $(INCLUUDE) $(LD_PATH) $(LIB) $(OPT) -c $(SRC)

.PHONY: clean install
clean:
	$(RM) *.o $(TARGET)

install:
	$(INSTALL) $(TARGET) $(LIB_DIR)
