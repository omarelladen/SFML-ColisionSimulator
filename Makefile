CXX = g++
CXXFLAGS = -Wall -Wextra
LDFLAGS = `pkg-config --libs sfml-graphics`

SRC = src/*.cpp
BIN = simulator

all: $(BIN)

$(BIN): $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

run: $(BIN)
	./$<

clean:
	rm -f $(BIN)
