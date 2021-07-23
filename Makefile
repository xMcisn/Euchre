output: Euchre.o Deck.o IPC.o Player.o Team.o
	g++ Euchre.o Deck.o IPC.o Player.o Team.o -o output

Euchre.o: Euchre.cpp
	g++ -c Euchre.cpp

Deck.o: Deck.cpp Deck.h
	g++ -c Deck.cpp

IPC.o: IPC.cpp IPC.h
	g++ -c IPC.cpp

Player.o: Player.cpp Player.h
	g++ -c Player.cpp

Team.o: Team.cpp Team.h
	g++ -c Team.cpp

clean:
	rm *.o output
