CXX         = clang++
# CXXFLAGS    = -std=c++17 -I/opt/homebrew/include -I./lib/include -Wall -Wextra -pedantic
CXXFLAGS    = -std=c++17 -I/opt/homebrew/include -I./lib/include 
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


# # CXX = clang++
# # CXXFLAGS = -Wall -std=c++17 -Iinclude
# # LDFLAGS = -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system

# # SRC_DIR = src
# # INC_DIR = include
# # OBJ_DIR = build
# # BIN_DIR = bin

# # SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
# # OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))
# # TARGET = $(BIN_DIR)/MiJuego

# # $(TARGET): $(OBJECTS)
# # 	@mkdir -p $(BIN_DIR)
# # 	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# # $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
# # 	@mkdir -p $(OBJ_DIR)
# # 	$(CXX) $(CXXFLAGS) -c $< -o $@

# # clean:
# # 	rm -rf $(OBJ_DIR) $(BIN_DIR)

# # .PHONY: clean

# # Compilador
# CXX = clang++
# # Flags del compilador
# CXXFLAGS = -std=c++17 -I/opt/homebrew/include -include
# # Nombre del ejecutable
# TARGET = CoreDumpers


# # Librerías a enlazar
# LDFLAGS = -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system
# # Archivos fuente
# SRCS = main.cpp
# # Archivos objeto
# OBJS = $(SRCS:.cpp=.o)

# # Regla por defecto
# all: $(TARGET)

# # Cómo construir el ejecutable
# $(TARGET): $(OBJS)
# 	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# # Cómo compilar archivos .cpp a .o
# %.o: %.cpp
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# # Limpiar archivos generados
# clean:
# 	rm -f $(TARGET) $(OBJS)


# CXX         = clang++ -std=c++17
# WARN        = -Wall -Wextra -Wcast-align -Wno-sign-compare -Wno-write-strings -Wno-parentheses -Wfloat-equal -pedantic

# # Libs
# LIB         = ./lib
# INCLUDES    = $(wildcard $(LIB)/include/*.hpp)
# SOURCES     = $(wildcard $(LIB)/src/*.cpp)
# OBJECTS     = $(SOURCES:$(LIB)/src/%.cpp=$(LIB)/obj/%.o)

# # Test
# TESTDIR     = ./test
# TEST        = $(wildcard $(TESTDIR)/src/*.cpp)
# MKTEST      = $(TEST:$(TESTDIR)/src/%.cpp=$(TESTDIR)/bin/%)

# INCLUDEPATH = -I$(LIB)/include

# FLAGS       = -Ofast $(WARN)
# LIBLINK     =  $(OBJECTS)

# all: test

# $(LIB)/obj/%.o : $(LIB)/src/%.cpp
# 	$(CXX) $(FLAGS) $(INCLUDEPATH) -c $< -o $@

# $(TESTDIR)/bin/%: $(TESTDIR)/src/%.cpp $(OBJECTS)
# 	$(CXX) $(FLAGS) $(INCLUDEPATH) $< -o $@ $(LIBLINK)

# test: $(TEST) $(INCLUDES) $(SOURCES) $(MKTEST)

# .PHONY:
# clean:
# 	$(RM) $(MKTEST)