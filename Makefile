all: build

build: planificator.c
	gcc -Wall planificator.c -o planificator

run: planificator
	@./planificator &

clean:
	rm -rf planificator

copy: build
	cp planificator ./checker/planificare