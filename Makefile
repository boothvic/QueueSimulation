OBJS = queue.o bank.o
bank: $(OBJS)
	g++ $^ -o $@
%.o: %.cpp
	g++ -c $< -o $@
clean: 
	rm -f *.o bank

