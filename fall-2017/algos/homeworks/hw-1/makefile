COMPILER=g++
OBJECT_FIlES=product.o tests.o

all: product

product: $(OBJECT_FIlES) 
	$(COMPILER) -o $(OBJECT_FIlES)

product.o: product.cpp product.h
	$(COMPILER) -o product.o -c product.cpp

tests.o: product_test_main.cpp 
	$(COMPILER) -o tests.o -c product_test_main.cpp product_test_suites.cpp

clean: 
	rm *.o product
