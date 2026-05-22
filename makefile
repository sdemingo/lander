all:
	cmake -B build
	cmake --build build


clean:
	rm -r build
