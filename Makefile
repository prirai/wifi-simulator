# Compiler
CXX = g++

# C++ standard
CXX_STANDARD = -std=c++20

# Debug build flags
DEBUG_FLAGS = -g

# Release build flags
RELEASE_FLAGS = -O3

# Source files
SOURCE_FILES = AccessPoint.cpp Packet.cpp Simulator.cpp User.cpp WiFiAccessPoints.cpp Utils.cpp WiFiChannel.cpp Globals.cpp

# Header files
HEADER_FILES = AccessPoint.h Packet.h Simulator.h User.h WiFiAccessPoints.h Utils.h WiFiChannel.h Globals.h

# Main executable source file
MAIN_SOURCE = main.cpp

# Object files
OBJECT_FILES = $(SOURCE_FILES:.cpp=.o)

# Static library
LIBRARY = libWiFiSimLib.a

all: debug optimized
# Debug build
debug: CXX_FLAGS = $(CXX_STANDARD) $(DEBUG_FLAGS)
debug: $(LIBRARY)
	$(CXX) $(CXX_FLAGS) $(MAIN_SOURCE) -o debug -L. -lWiFiSimLib

# Release build
optimized: CXX_FLAGS = $(CXX_STANDARD) $(RELEASE_FLAGS)
optimized: $(LIBRARY)
	$(CXX) $(CXX_FLAGS) $(MAIN_SOURCE) -o optimized -L. -lWiFiSimLib

# Static library compilation
$(LIBRARY): $(OBJECT_FILES)
	ar rcs $@ $^

# Object file compilation
%.o: %.cpp $(HEADER_FILES)
	$(CXX) $(CXX_STANDARD) -c $< -o $@

# Clean
clean:
	rm -f $(OBJECT_FILES) $(LIBRARY) debug optimized
