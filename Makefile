watan: main.o cell.o tile.o display.o player.o board.o maps.o
	g++ -g -Werror=vla main.o board.o cell.o tile.o player.o display.o maps.o -o watan
main.o: main.cc cell.h tile.h player.h display.h board.h phase.h observer.h subject.h
	g++ -g -Werror=vla -std=c++14 -c main.cc
cell.o: cell.cc cell.h observer.h subject.h phase.h player.h
	g++ -g -Werror=vla -std=c++14 -c cell.cc
tile.o: tile.cc tile.h subject.h phase.h
	g++ -g -Werror=vla -std=c++14 -c tile.cc
display.o: display.cc display.h observer.h subject.h phase.h tile.h maps.h
	g++ -g -Werror=vla -std=c++14 -c display.cc
player.o: player.cc player.h observer.h subject.h phase.h cell.h
	g++ -g -Werror=vla -std=c++14 -c player.cc
board.o: board.cc board.h observer.h subject.h phase.h player.h display.h tile.h cell.h maps.h
	g++ -g -Werror=vla -std=c++14 -c board.cc
maps.o: maps.cc maps.h
	g++ -g -Werror=vla -std=c++14 -c maps.cc 

.PHONY: clean
clean:
	rm *.o watan