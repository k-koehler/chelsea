CC=clang++
CCFLAGS=-Weverything -Wno-c++11-extensions -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded -Wno-missing-prototypes -Wno-c99-extensions -std=c++17
TARGET=chc

SRCPATH=src
LEXPATH=$(SRCPATH)/lex

default: main	

main: lex.o
	@$(CC) $(CCFLAGS) $(SRCPATH)/main.cc lex.o -o $(TARGET) 

TEST_LEX_TARGET=chc_test_lex
test_lex: lex.o
	@$(CC) $(CCFLAGS) $(LEXPATH)/test_lex.cc lex.o -o $(TEST_LEX_TARGET) || make clean
	@./$(TEST_LEX_TARGET) || make clean
	@make clean

lex.o: $(LEXPATH)/lex.cc $(LEXPATH)/lex.hpp
	@$(CC) $(CCFLAGS) -c $(LEXPATH)/lex.cc

TARGETS = $(TARGET) $(TEST_LEX_TARGET)

clean:
	@$(RM) count *.o *~ $(TARGETS)
	