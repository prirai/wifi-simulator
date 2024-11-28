CXX = g++
CXX_STANDARD = -std=c++20
DEBUG_FLAGS = -g
RELEASE_FLAGS = -O3

SOURCE_FILES = AccessPoint.cpp Packet.cpp Simulator.cpp User.cpp WiFiAccessPoints.cpp Utils.cpp WiFiChannel.cpp Globals.cpp
HEADER_FILES = AccessPoint.h Packet.h Simulator.h User.h WiFiAccessPoints.h Utils.h WiFiChannel.h Globals.h
MAIN_SOURCE = main.cpp
OBJECT_FILES = $(SOURCE_FILES:.cpp=.o)

LIBRARY = libWiFiSimLib.a

all: debug optimized

debug: CXX_FLAGS = $(CXX_STANDARD) $(DEBUG_FLAGS)
debug: $(LIBRARY)
	$(CXX) $(CXX_FLAGS) $(MAIN_SOURCE) -o debug -L. -lWiFiSimLib

optimized: CXX_FLAGS = $(CXX_STANDARD) $(RELEASE_FLAGS)
optimized: $(LIBRARY)
	$(CXX) $(CXX_FLAGS) $(MAIN_SOURCE) -o optimized -L. -lWiFiSimLib

$(LIBRARY): $(OBJECT_FILES)
	ar rcs $@ $^

%.o: %.cpp $(HEADER_FILES)
	$(CXX) $(CXX_STANDARD) -c $< -o $@

clean:
	rm -f $(OBJECT_FILES) $(LIBRARY) debug optimized
