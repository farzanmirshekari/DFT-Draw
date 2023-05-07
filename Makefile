all: fourier_visualizer

fourier_visualizer: Arm.o Complex.o main.o SVG_data.o
	g++ -Wall -Wextra -std=c++17 -I/usr/include/SFML -o $@ $^ -lsfml-graphics -lsfml-window -lsfml-system
	rm -f Arm.o Complex.o main.o SVG_data.o

%.o: %.cpp
	g++ -Wall -Wextra -std=c++17 -I/usr/include/SFML -c -o $@ $<