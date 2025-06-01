CXX         = clang++
# MACOS
CXXFLAGS    = -std=c++17 -I/opt/homebrew/include -I./lib/include -I/usr/local/include
LDFLAGS     = -L/opt/homebrew/lib -L/usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system -lbox2d
# END - MACOS
# # LINUX
# CXXFLAGS    = -std=c++17 -I/usr/local/include -I./lib/include
# LDFLAGS     = -L/usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system  -lbox2d
# END - LINUX
WARN        = -Wall -Wextra -pedantic
# WARN        = -Wall -Wextra -Wcast-align -Wno-sign-compare -Wno-write-strings -Wno-parentheses -Wfloat-equal -pedantic

# Lib
LIB         = ./lib
INCLUDES    = $(wildcard $(LIB)/include/*.hpp)
SOURCES     = $(wildcard $(LIB)/src/*.cpp)
OBJECTS     = $(SOURCES:$(LIB)/src/%.cpp=$(LIB)/obj/%.o)

# Main file
MAIN        = main.cpp
MAINOBJ     = $(MAIN:.cpp=.o)

# Ejecutable
TARGET      = CoreDumpers

# --- Compilación principal ---
all: $(TARGET)

$(TARGET): $(MAINOBJ) $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(WARN) $^ -o $@ $(LDFLAGS)

# Compilar archivos fuente de lib
$(LIB)/obj/%.o : $(LIB)/src/%.cpp
	@mkdir -p $(LIB)/obj
	$(CXX) $(CXXFLAGS) $(WARN) -c $< -o $@

# Compilar main.cpp
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(WARN) -c $< -o $@

# --- Limpieza ---
clean:
	rm -f $(TARGET) $(MAINOBJ) $(OBJECTS)

.PHONY: all clean

