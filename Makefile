make: dbms

dbms: dbms.o Parser.o
	g++ -o dbms dbms.o Parser.o

dbms.o: dbms.cpp Parser.h
	g++ -std=c++11 -c dbms.cpp

Parser.o: Parser.cpp Parser.h Table.o Engine.o
	g++ -std=c++11 -c Parser.cpp

Table.o: Table.cpp Table.h
	g++ -std=c++11 -c Table.cpp

Engine.o: Engine.cpp Engine.h
	g++ -std=c++11 -c Engine.cpp

clean:
	rm -rf *.o dbms
