CC = clang++
CFLAGS = -std=c++11 -Wall
LFLAGS = -stdlib=libc++

all: rpn-print rpn
rpn-print: rpn-print.cpp RpnParser.cpp
	$(CC) $(CFLAGS) -o rpn-print $(LFLAGS) rpn-print.cpp RpnParser.cpp

rpn: rpn.cpp RpnParser.cpp
	$(CC) $(CFLAGS) -o rpn $(LFLAGS) rpn.cpp RpnParser.cpp

clean:
	$(RM) rpn rpn-print
