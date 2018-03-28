CMP=g++ -std=c++14 -Wall -O3 -fopenmp
LINKER=-L/usr/local -lcnpy -lz
NAME=img-processor
FILES=processor.cpp bin-img-io.cpp

all: $(NAME).out

$(NAME).out: $(FILES)
	$(CMP) -o $(NAME).out $(FILES) $(LINKER)

run: all
	./$(NAME).out

clean:
	rm $(NAME).out
