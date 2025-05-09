CXX         = clang++
CXXFLAGS    = -std=c++17 -I/opt/homebrew/include -I./lib/include -Wall -Wextra -pedantic
# CXXFLAGS    = -std=c++17 -I/opt/homebrew/include -I./lib/include 
LDFLAGS     = -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system

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
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Compilar archivos fuente de lib
$(LIB)/obj/%.o : $(LIB)/src/%.cpp
	@mkdir -p $(LIB)/obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilar main.cpp
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# --- Limpieza ---
clean:
	rm -f $(TARGET) $(MAINOBJ) $(OBJECTS)

.PHONY: all clean

