CMP=g++ -std=c++14
OFILES=main.o suites.o

all: ksarray

ksarray: $(OFILES)
	$(CMP) -o ksarray $(OFILES)

suites.o: ksarray_test_suites.cpp ksarray.h
	$(CMP) -o suites.o -c ksarray_test_suites.cpp

main.o: ksarray_test_main.cpp catch.hpp 
	$(CMP) -o main.o -c ksarray_test_main.cpp 

clean:
	rm $(OFILES) ksarray
