TARGET=top
BUILD_DIR=build


CC_SOURCES = \
  src/display.cpp \
  ../top/src/stack_mem.cpp \
  ../top/src/top.cpp

C++ = g++
C_INCLUDES = -Iinc
C_INCLUDES += -I../top/inc
CFLAGS = $(C_INCLUDES)
CFLAGS += -g


all: $(BUILD_DIR)/$(TARGET)
	cp $(BUILD_DIR)/$(TARGET) .


OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(CC_SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CC_SOURCES)))

$(BUILD_DIR)/%.o: %.cpp makefile | $(BUILD_DIR)
	$(C++) -c $(CFLAGS) $< -o $@


$(BUILD_DIR)/$(TARGET): $(OBJECTS) makefile
	$(C++) $(OBJECTS) -o $@ -lsfml-graphics -lsfml-window -lsfml-system

$(BUILD_DIR):
	mkdir -p $@
