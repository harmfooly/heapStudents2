heapStudents2: students.o
	g++ students.o -o heapStudents2

students.o: students.cpp
	g++ -c students.cpp

clean:
	rm *.o
	rm heapStudents2

run: heapStudents2
	./heapStudents2
