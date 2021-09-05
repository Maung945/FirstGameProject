all:Game

Game: Game.cpp
	g++ -o $@ $<

clean:
	rm -f Game?

