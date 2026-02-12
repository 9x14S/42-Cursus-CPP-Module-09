.PHONY     : all re clean fclean

TARGET     := btc

CXX        := /usr/bin/c++
CXXFLAGS   := -Wall -Wextra -Werror -MMD -std=c++98 -I.

BUILD_DIR  := build
SRCS       := main.cpp
OBJS       := $(SRCS:%.cpp=$(BUILD_DIR)/%.o)
DEPS       := $(OBJS:.o=.d)

# Target dependency tree
all: $(BUILD_DIR) $(TARGET)
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Output directory
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Compilation
-include $(DEPS)
$(BUILD_DIR)/%.o: %.cpp Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cleaning
clean:
	rm -f $(OBJS) $(DEPS)
	rm -rf $(BUILD_DIR)
fclean: clean
	rm -f $(TARGET)
re: fclean all
