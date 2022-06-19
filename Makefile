EXECUTABLE 	= elfparser

SOURCES = $(shell find . -name "*.c")
HEADERS = $(shell find . -name "*.h")

OBJECTS = $(patsubst %.c, %.o, $(SOURCES))
DEPENDS = $(patsubst %.c, %.d, $(SOURCES))

CFLAGS = -g -Wall
LDFLAGS =

INC = -I ./includes

all: $(EXECUTABLE)

%.o: %.c
	@echo "Compiling dependancies ..."
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(EXECUTABLE): $(OBJECTS)
	@$(CC) $(INC) $(OBJECTS) $(LDFLAGS) -o $(EXECUTABLE)
	@echo "Compiled !"

.phony: clean
clean:
	-@$(RM) $(OBJECTS) $(DEPENDS)
	@echo "Everything is Cleaned !"

.phony: fclean
fclean: clean
	-@$(RM) $(EXECUTABLE)

.phony: run
run: all
	$(EXECUTABLE)

.phony: re
re: clean all

-include $(DEPENDS)