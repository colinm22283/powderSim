all:
	g++ -std=c++17 -I ./header -o ./powder ./source/*.cpp ./scripts/*.cpp -L"lib" -Wall -lSDL2main -lSDL2 -lSDL2_ttf -pthread
	./powder
compile:
	g++ -std=c++17 -I ./header -o ./powder ./source/*.cpp ./scripts/*.cpp -L"lib" -Wall -lSDL2main -lSDL2 -lSDL2_ttf -pthread
run:
	./powder
push:
	read desc
	git commit -a -m "$desc"
	git push origin main
