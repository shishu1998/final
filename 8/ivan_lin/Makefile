all: ./dirinfo ./editor

./dirinfo: dirinfo.c
	gcc -o dirinfo dirinfo.c

./editor: editor.c
	gcc -o editor editor.c

run: 
	make all
	./dirinfo
	./editor
