build: main.cc
	@clang++ -std=c++2b -pthread ${?} -o game	

run: game
	@./${?}
