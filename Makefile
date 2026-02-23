CXX = g++
CXXFLAGS = -Wall -Wextra
LDFLAGS = `pkg-config --libs sfml-graphics`

SOURCES = src/*.cpp
TARGET = simulator

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(SOURCES) -o $(TARGET) $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -f $(TARGET)
