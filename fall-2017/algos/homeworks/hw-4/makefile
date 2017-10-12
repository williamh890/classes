CMP=g++ -std=c++11 -pthread -Wall 
NAME=counthsr
THREAD=
OFILES=main.o suites.o $(NAME).o

all: $(NAME).out

$(NAME).out: $(OFILES)
	$(CMP) -o $(NAME).out $(OFILES) $(THREADS) 

suites.o: $(NAME)_test_suites.cpp $(NAME).h
	$(CMP) -o suites.o $(THREADS) -c $(NAME)_test_suites.cpp

main.o: $(NAME)_test_main.cpp catch.hpp 
	$(CMP) -o main.o $(THREADS) -c $(NAME)_test_main.cpp 

$(NAME).o: $(NAME).cpp $(NAME).h
	$(CMP) -o $(NAME).o $(THREADS) -c $(NAME).cpp

clean:
	rm *.o *.out
