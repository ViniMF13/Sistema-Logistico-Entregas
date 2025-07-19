# Compilador
CXX = g++
CXXFLAGS = -Wall -std=c++11 -Iinclude

# Pastas
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include

# Arquivos
TARGET = $(BIN_DIR)/tp2.out

# Lista de arquivos fonte
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

# Regra principal
all: $(TARGET)

# Linkagem final
$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilação dos .cpp
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpar arquivos
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

.PHONY: all clean