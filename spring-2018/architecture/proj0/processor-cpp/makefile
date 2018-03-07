CMP=g++ -std=c++14 -Wall -O3 -fopenmp
NAME=img-processor
FILES=processor.cpp

all: $(NAME).out

$(NAME).out: $(FILES)
	$(CMP) -o $(NAME).out $(FILES)

run: all
	./$(NAME).out

clean:
	rm $(NAME).out
