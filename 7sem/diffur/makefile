# Variables
CC = g++
CFLAGS = -Wall -Wextra -O2 -g -pg
OBJDIR = obj
SRCDIR = src
BINDIR = bin
TARGET = $(BINDIR)/a.out
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
DEPS = $(OBJS:.o=.d)

# Phony Targets
.PHONY: all clean profile

# Default Target
all: $(TARGET)

# Compile Object Files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Generate Dependencies
$(OBJDIR)/%.d: $(SRCDIR)/%.cpp
	$(CC) -MM $< > $@

# Link Object Files
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Include Dependencies
-include $(DEPS)

# Profile Target
profile: $(TARGET)
	./$(TARGET)
	gprof $(TARGET) gmon.out > profile.txt

# Clean Target
clean:
	rm -f $(OBJDIR)/*.o $(OBJDIR)/*.d $(TARGET) gmon.out profile.txt