CC = g++
CCFLAGS = -g -O3 -Wall -Wshadow -Wconversion -D_THREAD_SAFE -D_REENTRANT

SOURCES = h_.cpp \
          h_node.cpp
	
%.o: %.cpp
	$(CC) $(CCFLAGS) -c $< -o $@

	
libh_.a: $(SOURCES:.cpp=.o)
	$(AR) rc ../$@ $^
	ranlib ../$@
	$(RM) *.o
	
.PHONY: clean count
clean:
	@ $(RM) *.o ../*.a

count:
	@ wc -l *.cpp *.h | sort
