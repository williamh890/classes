CMP=g++ -std=c++14 -Wall
NAME=da6
OFILES=main.o suites.o 

all: $(NAME).out

$(NAME).out: $(OFILES)
	$(CMP) -o $(NAME).out $(OFILES)

suites.o: $(NAME)_test_suites.cpp $(NAME).h
	$(CMP) -o suites.o -c $(NAME)_test_suites.cpp

main.o: $(NAME)_test_main.cpp catch.hpp
	$(CMP) -o main.o -c $(NAME)_test_main.cpp

clean:
	rm $(OFILES) ksarray
