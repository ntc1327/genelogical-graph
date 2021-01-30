OBJECTS = person.o family.o list.o main.o
HEADERS = person.h family.h list.h
Project4: $(OBJECTS)
	g++ $^ -o $@

%.o: %.cpp $(HEADERS)
	g++ -c $< -o $@

clean:
	rm -i *.o Project4

run:
	./Project4 finkelData.txt myData.txt

