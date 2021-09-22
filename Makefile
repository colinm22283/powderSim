all:
	g++ -std=c++17 -I ./header -I ./scripts/header -o ./powder ./source/*.cpp ./scripts/source/*.cpp -L"lib" -Wall -lSDL2main -lSDL2 -lSDL2_ttf -pthread
	./powder
compile:
	g++ -std=c++17 -I ./header -I ./scripts/header -o ./powder ./source/*.cpp ./scripts/source/*.cpp -L"lib" -Wall -lSDL2main -lSDL2 -lSDL2_ttf -pthread
run:
	./powder
push:
	git add ./header ./source ./scripts/header ./scripts/source
	git commit -a -m "1.0"
	git push origin main
