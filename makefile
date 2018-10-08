all:
	g++ -g demo_serialization.cpp -o demo_serialization -lpthread -lm 

clean:
	rm demo_serialization

