CXX = g++ 
CXXFLAGS = `pkg-config --cflags sfml-graphics sfml-window sfml-system`
LDFLAGS = `pkg-config --libs sfml-graphics sfml-window sfml-system`

SOURCES = src/Ball.cpp src/ColisionSimulator.cpp src/Simulator.cpp
TARGET = simulator

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(SOURCES) -o $(TARGET) $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -f $(TARGET)
