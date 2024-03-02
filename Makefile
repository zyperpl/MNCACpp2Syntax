CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic -O3 -march=native -I cppfront/source -I raylib/src -L raylib/src -lraylib -lGL -lm

CPPFRONT = cppfront/cppfront

all: mnca

mnca: mnca.cpp raylib
	$(CXX) -o mnca mnca.cpp $(CXXFLAGS)

mnca.cpp: mnca.cpp2 $(CPPFRONT)
	$(CPPFRONT) mnca.cpp2

$(CPPFRONT):
	git clone https://github.com/hsutter/cppfront cppfront
	cd cppfront && git reset --hard d59ef7c
	$(CXX) -std=c++20 -o $(CPPFRONT) cppfront/source/cppfront.cpp

raylib:
	git clone --depth 1 --branch 5.0 https://github.com/raysan5/raylib
	cd raylib/src && make -j8

clean:
	rm -f mnca mnca.cpp $(CPPFRONT)
	rm -rf cppfront
	rm -rf raylib
