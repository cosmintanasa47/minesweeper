all:
	gcc mine.c -o mine -Wall
	./mine
	rm -f mine
