.PHONY: all debug release clean

Compiler = g++
RELEASE_FLAGS = -Wall -DNDEBUG -Theaders
DEBUG_FLAGS = -g -Wall -Theaders
RELEASE_EXEC = hash_exe
DEBUG_EXEC = hash_exe-dbg
SOURCES = hash_exe.cpp
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
