all:
	g++ -std=c++17 -I ./header -I ./source/header -o ./powder ./source/*.cpp ./scripts/source/*.cpp -L"lib" -Wall -lSDL2main -lSDL2 -lSDL2_ttf -pthread
	./powder
compile:
	g++ -std=c++17 -I ./header -I ./source/header -o ./powder ./source/*.cpp ./scripts/source/*.cpp -L"lib" -Wall -lSDL2main -lSDL2 -lSDL2_ttf -pthread
run:
	./powder
push:
	read version
	echo $version
	git commit -a -m $version
	git push origin main
