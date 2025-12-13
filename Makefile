# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -std=c++20

# Windows API libs
LIBS := -lpsapi -liphlpapi -lws2_32 -ldxgi -ld3d12 -lntdll #-static

# Sources and Output
SRC := src/winfetch.cpp src/lib.cpp src/ascii.cpp
OUT := winfetch.exe

# Commands
all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LIBS)

run: $(OUT)
	./$(OUT)

clean:
	rm -f $(OUT)
	