CC=g++
CFLAGS= -c -Wall -std=c++14
EXENAME= M05
default: main.o SemanticDescriptor.o SemanticDictionary.o
	$(CC) main.o SemanticDescriptor.o SemanticDictionary.o -o $(EXENAME)
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
SemanticDescriptor.o: SemanticDescriptor.cpp
	$(CC) $(CFLAGS) SemanticDescriptor.cpp
SemanticDictionary.o: SemanticDictionary.cpp
	$(CC) $(CFLAGS) SemanticDictionary.cpp
clean:
	rm *o $(EXENAME)
run:
	./$(EXENAME)