CFLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations  \
-Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wconversion 						\
-Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers 			\
-Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel 			\
-Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE -fsanitize=address

TARGET = ./test.exe
COMPILER = g++

start: tree.o tree_dump.o akinator.o test.o
	$(COMPILER) tree.o tree_dump.o akinator.o test.o -o $(TARGET) $(CFLAGS)
	$(TARGET)

tree.o : tree/tree.cpp
	$(COMPILER) tree/tree.cpp -c

tree_dump.o : tree_dump/tree_dump.cpp
	$(COMPILER) tree_dump/tree_dump.cpp -c

akinator.o : akinator/akinator.cpp
	$(COMPILER) akinator/akinator.cpp -c

test.o : test.cpp
	$(COMPILER) test.cpp -c

clean:
	rm -f $(TARGET)
	rm -f *.o
	rm -f *.out
	rm -f *.exe
	rm -f *.dot
	rm -f tree_dump/dumps/dumps/*.html
