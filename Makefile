all: dft_draw

dft_draw: Arm.o Complex.o main.o SVG_data.o
	g++ -Wall -Wextra -std=c++17 -I/opt/homebrew/Cellar/sfml/2.5.1_2/include/ -o $@ $^ -L/opt/homebrew/Cellar/sfml/2.5.1_2/lib/ -lsfml-graphics -lsfml-window -lsfml-system
	rm -f Arm.o Complex.o main.o SVG_data.o

%.o: %.cpp
	g++ -Wall -Wextra -std=c++17 -I/opt/homebrew/Cellar/sfml/2.5.1_2/include/ -c $<