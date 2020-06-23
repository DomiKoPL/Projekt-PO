CC := g++
FLAGS := -O3 -std=c++17 -g -Wall -Wextra -pedantic-errors -Wfatal-errors 
#-fsanitize=address -fsanitize=undefined -g
SFML_LIBS := $(shell pkg-config sfml-all --libs)
TARGET := gra

SRCS := $(wildcard src/*.cpp)\
		$(wildcard src/screens/*.cpp)\
		$(wildcard src/gui/*.cpp)\
		$(wildcard src/colliders/*.cpp)\
		$(wildcard src/enemies/*.cpp)\
		$(wildcard src/levels/*.cpp)

#* tutaj trzeba dopisac foldery tak jak w przykladzie nizej
# SRCS := $(wildcard src/*.cpp) \
# 		$(wildcard src/screens/*.cpp)\
# 		$(wildcard src/gui/*.cpp)\
# 		$(wildcard src/effects/*.cpp)\
# 		$(wildcard src/settings/*.cpp)

OBJ := $(addprefix obj/, $(notdir $(patsubst %.cpp,%.o,$(SRCS))))

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(FLAGS) $(SFML_LIBS) -o $@

obj/%.o: src/%.cpp src/%.hpp
	$(CC) $(FLAGS) -c $< -o $(addprefix obj/, $(notdir $(patsubst %.cpp,%.o,$<)))

obj/%.o: src/screens/%.cpp src/screens/%.hpp
	$(CC) $(FLAGS) -c $< -o $(addprefix obj/, $(notdir $(patsubst %.cpp,%.o,$<)))

obj/%.o: src/gui/%.cpp src/gui/%.hpp
	$(CC) $(FLAGS) -c $< -o $(addprefix obj/, $(notdir $(patsubst %.cpp,%.o,$<)))

obj/%.o: src/colliders/%.cpp src/colliders/%.hpp
	$(CC) $(FLAGS) -c $< -o $(addprefix obj/, $(notdir $(patsubst %.cpp,%.o,$<)))

obj/%.o: src/enemies/%.cpp src/enemies/%.hpp
	$(CC) $(FLAGS) -c $< -o $(addprefix obj/, $(notdir $(patsubst %.cpp,%.o,$<)))

obj/%.o: src/levels/%.cpp src/levels/%.hpp
	$(CC) $(FLAGS) -c $< -o $(addprefix obj/, $(notdir $(patsubst %.cpp,%.o,$<)))

#* jezeli zostal dodany nowy folder to trzeba dla niego stworzyc zasade
# obj/%.o: src/gui/%.cpp src/gui/%.hpp
# 	$(CC) $(FLAGS) -c $< -o $(addprefix obj/, $(notdir $(patsubst %.cpp,%.o,$<)))

obj/%.o: src/%.cpp
	$(CC) $(FLAGS) -c $< -o $(addprefix obj/, $(notdir $(patsubst %.cpp,%.o,$<)))

clean:
	rm -rf $(TARGET) $(OBJ)
	
.PHONY: all clean