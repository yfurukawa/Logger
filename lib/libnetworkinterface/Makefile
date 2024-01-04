RM = rm -rf
CC = g++
AR = ar
CP = cp -Rf
INSTALL = install -m 644
INCLUUDE = -I/usr/include -I/usr/local/include
LD_PATH = -L/usr/lib64 -L/usr/local/lib64
LIB_DIR = /usr/local/lib64
INCLUDE_DIR = /usr/local/include
LIB = 
OPT = -O0 -Wall -std=c++17 -fPIC
TARGET = libnetworkinterface.a.0.1.0
SRC = UdpClient.cpp Port.cpp IPv4.cpp

$(TARGET):
	$(CC) $(INCLUUDE) $(OPT) -c $(SRC)
	$(AR) rc -o $(TARGET) $(SRC:.cpp=.o)

.PHONY: clean install
clean:
	$(RM) *.o $(TARGET)

install:
	$(INSTALL) $(TARGET) $(LIB_DIR)
	$(CP) *.h $(INCLUDE_DIR)
	$(CP) skills/ $(INCLUDE_DIR)
