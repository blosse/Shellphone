
# Makefile for building the audio player with PortAudio
# Generated by Chatis :(

# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -I/opt/homebrew/include

# Linker Flags
LDFLAGS = -L/opt/homebrew/lib -lportaudio

# Target executable
TARGET = player

# Source files
SRC = main.cpp

# Rule to build the target
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(SRC) -o $(TARGET) $(CXXFLAGS) $(LDFLAGS)

# Clean up
clean:
	rm -f $(TARGET)
