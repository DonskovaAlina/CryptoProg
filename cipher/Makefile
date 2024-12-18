.PHONY: all debug release clean

Compiler = g++
RELEASE_FLAGS = -Wall -DNDEBUG
DEBUG_FLAGS = -g -Wall
RELEASE_EXEC = chiper
DEBUG_EXEC = chiper.dbg
SOURCES = chiper.cpp
LIBARY = -lcryptopp

all: debug release

debug: $(DEBUG_EXEC)

$(DEBUG_EXEC): $(SOURCES)
	$(Compiler) $(DEBUG_FLAGS) $(SOURCES) -o $(DEBUG_EXEC) $(LIBARY)

release: $(RELEASE_EXEC)

$(RELEASE_EXEC): $(SOURCES)
	$(Compiler) $(RELEASE_FLAGS) $(SOURCES) -o $(RELEASE_EXEC) $(LIBARY)

clean:
	rm -f $(RELEASE_EXEC) $(DEBUG_EXEC)
