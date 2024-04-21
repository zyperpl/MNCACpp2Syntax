CXXFLAGS = -std=c++20 -Wall -Wextra -Wpedantic -Wno-missing-field-initializers -O3 -march=native -I cppfront/source -ggdb

CPPFRONT = cppfront/cppfront
OUT_DIR = build
SRC_DIR = src
UTILS_SRC_DIR = utils

all: create_dirs $(OUT_DIR)/mnca

create_dirs: 
	mkdir -p $(OUT_DIR)

$(OUT_DIR)/mnca: $(OUT_DIR)/font.cpp $(OUT_DIR)/gui.cpp $(OUT_DIR)/mnca.cpp $(SRC_DIR)/build.cpp $(CPPFRONT) raylib
	$(CXX) $(CXXFLAGS) -I $(OUT_DIR) -o $(OUT_DIR)/mnca $(SRC_DIR)/build.cpp -I raylib/src -L raylib/src -l raylib -lm

$(OUT_DIR)/font.cpp: $(CPPFRONT) $(SRC_DIR)/font.cpp2 
	$(CPPFRONT) -o $(OUT_DIR)/font.cpp $(SRC_DIR)/font.cpp2

$(OUT_DIR)/gui.cpp: $(CPPFRONT) $(OUT_DIR)/font_data.h $(SRC_DIR)/gui.cpp2 $(OUT_DIR)/types.h $(OUT_DIR)/utils.h $(OUT_DIR)/config.h
	$(CPPFRONT) -o $(OUT_DIR)/gui.cpp $(SRC_DIR)/gui.cpp2

$(OUT_DIR)/mnca.cpp: $(CPPFRONT) $(SRC_DIR)/mnca.cpp2 $(OUT_DIR)/types.h $(OUT_DIR)/utils.h $(OUT_DIR)/config.h
	$(CPPFRONT) -no-subscript-checks -o $(OUT_DIR)/mnca.cpp $(SRC_DIR)/mnca.cpp2

$(OUT_DIR)/types.h: $(CPPFRONT) $(SRC_DIR)/types.h2
	$(CPPFRONT) -o $(OUT_DIR)/types.h $(SRC_DIR)/types.h2

$(OUT_DIR)/utils.h: $(CPPFRONT) $(SRC_DIR)/utils.h2
	$(CPPFRONT) -o $(OUT_DIR)/utils.h $(SRC_DIR)/utils.h2

$(OUT_DIR)/config.h: $(CPPFRONT) $(SRC_DIR)/config.h2
	$(CPPFRONT) -o $(OUT_DIR)/config.h $(SRC_DIR)/config.h2

$(OUT_DIR)/font_data.h: $(SRC_DIR)/font_data.h2
	$(CPPFRONT) -o $(OUT_DIR)/font_data.h $(SRC_DIR)/font_data.h2

$(SRC_DIR)/font_data.h2: $(OUT_DIR)/file2cpp2 resources/Inter-Medium.ttf
	$(OUT_DIR)/file2cpp2 resources/Inter-Medium.ttf > $(SRC_DIR)/font_data.h2

$(SRC_DIR)/font_data.h2: $(OUT_DIR)/file2cpp2 resources/Inter-SemiBold.ttf
	$(OUT_DIR)/file2cpp2 resources/Inter-SemiBold.ttf > $(SRC_DIR)/font_data.h2

$(OUT_DIR)/file2cpp2: $(OUT_DIR)/file2cpp2.cpp raylib
	$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/file2cpp2 $(OUT_DIR)/file2cpp2.cpp -I raylib/src/ -L raylib/src -lraylib -lm

$(OUT_DIR)/file2cpp2.cpp: $(CPPFRONT) $(UTILS_SRC_DIR)/file2cpp2.cpp2 
	$(CPPFRONT) -o $(OUT_DIR)/file2cpp2.cpp $(UTILS_SRC_DIR)/file2cpp2.cpp2

$(CPPFRONT):
	test -d cppfront || git clone https://github.com/hsutter/cppfront cppfront
	cd cppfront && git reset --hard d59ef7c
	$(CXX) -std=c++20 -O3 -o $(CPPFRONT) cppfront/source/cppfront.cpp

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
