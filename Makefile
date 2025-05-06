TARGET = executable

COMPILER = g++

FLAGS = -Wall -g

LIBS = -lGL -lGLU -lglut

SOURCES = main.cpp \
					window/window.cpp\
					elements/base/base.cpp\
					elements/gripper/gripper.cpp\
					elements/forearm/forearm.cpp\
					elements/upper_arm/upper_arm.cpp\
					elements/joint/joint.cpp

OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)
	
%.o: %.cpp
	$(COMPILER) $(FLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(COMPILER) $(FLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f $(TARGET) $(OBJECTS)
