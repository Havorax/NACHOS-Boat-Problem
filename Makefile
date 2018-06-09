boat:
	g++ boat.cpp -o boat -pthread -std=c++11 -O3 

run:
	./boat 2 2 1

clean:
	rm boat