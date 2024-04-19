CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic -O3 -march=native -I cppfront/source -ggdb

CPPFRONT = cppfront/cppfront
OUT_DIR = build

all: create_dirs mnca

create_dirs: 
	mkdir -p $(OUT_DIR)

mnca: $(OUT_DIR)/gui.cpp $(OUT_DIR)/mnca.cpp build.cpp $(CPPFRONT) raylib
	$(CXX) $(CXXFLAGS) -I $(OUT_DIR) -o $(OUT_DIR)/mnca build.cpp -I raylib/src -L raylib/src -l raylib -lm

$(OUT_DIR)/gui.cpp: $(CPPFRONT) gui.cpp2 $(OUT_DIR)/types.h $(OUT_DIR)/utils.h $(OUT_DIR)/config.h
	$(CPPFRONT) -o $(OUT_DIR)/gui.cpp gui.cpp2

$(OUT_DIR)/mnca.cpp: $(CPPFRONT) mnca.cpp2 $(OUT_DIR)/types.h $(OUT_DIR)/utils.h $(OUT_DIR)/config.h
	$(CPPFRONT) -no-subscript-checks -o $(OUT_DIR)/mnca.cpp mnca.cpp2

$(OUT_DIR)/types.h: $(CPPFRONT) types.h2
	$(CPPFRONT) -o $(OUT_DIR)/types.h types.h2

$(OUT_DIR)/utils.h: $(CPPFRONT) utils.h2
	$(CPPFRONT) -o $(OUT_DIR)/utils.h utils.h2

$(OUT_DIR)/config.h: $(CPPFRONT) config.h2
	$(CPPFRONT) -o $(OUT_DIR)/config.h config.h2

$(CPPFRONT):
	test -d cppfront || git clone https://github.com/hsutter/cppfront cppfront
	cd cppfront && git reset --hard d59ef7c
	$(CXX) -std=c++20 -o $(CPPFRONT) cppfront/source/cppfront.cpp

raylib:
	git clone --depth 1 --branch 5.0 https://github.com/raysan5/raylib
	cd raylib/src && make -j8

clean:
	rm -f $(OUT_DIR)/mnca
	rm -f $(OUT_DIR)/gui.h $(OUT_DIR)/gui.hpp $(OUT_DIR)/gui.cpp $(OUT_DIR)/mnca.cpp
	rm -f $(OUT_DIR)/types.h $(OUT_DIR)/utils.h $(OUT_DIR)/config.h
	rmdir $(OUT_DIR) 2>/dev/null || true
	rm -f $(CPPFRONT)
	rm -rf raylib
