#Burak Coskun	Furkan Demirelli	Eren Ozan Özmen
shell: lib/main.o lib/builtin.o lib/execute.o lib/parser.o lib/signals.o
	gcc lib/main.o lib/builtin.o lib/execute.o lib/parser.o lib/signals.o -o bin/shell

lib/main.o: src/main.c include/builtin.h include/execute.h include/parser.h include/signals.h include/utils.h
	gcc -Wall -Wextra -g -Iinclude -c src/main.c -o lib/main.o

lib/builtin.o: src/builtin.c include/builtin.h include/parser.h include/utils.h
	gcc -Wall -Wextra -g -Iinclude -c src/builtin.c -o lib/builtin.o

lib/execute.o: src/execute.c include/execute.h include/builtin.h include/parser.h include/signals.h include/utils.h
	gcc -Wall -Wextra -g -Iinclude -c src/execute.c -o lib/execute.o

lib/parser.o: src/parser.c include/parser.h include/utils.h
	gcc -Wall -Wextra -g -Iinclude -c src/parser.c -o lib/parser.o

lib/signals.o: src/signals.c include/signals.h include/utils.h
	gcc -Wall -Wextra -g -Iinclude -c src/signals.c -o lib/signals.o

clean:
	rm -f src/*.o bin/shell
