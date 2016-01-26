RESULT = main
HEADERS = board.h utils.h connections.h game.h
OBJECTS = main.o board.o utils.o connections.o game.o

%.o: %.c $(HEADERS)
	gcc -c -o $@ $<

$(RESULT): $(OBJECTS)
	gcc -o $@ $^

.PHONY: clean run

clean:
	-rm $(OBJECTS) $(RESULT)

run:
	./$(RESULT)