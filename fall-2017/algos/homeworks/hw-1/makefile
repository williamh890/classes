COMPILER=g++

product.out: product.o tests-main.o tests-suites.o
	$(COMPILER) -o product.out product.o tests-suites.o tests-main.o

product.o: product.cpp product.h
	$(COMPILER) -o product.o -c product.cpp

tests-main.o: product_test_main.cpp 
	$(COMPILER) -o tests-main.o -c product_test_main.cpp

tests-suites.o: product_test_suites.cpp catch.hpp
	$(COMPILER) -o tests-suites.o -c product_test_suites.cpp
