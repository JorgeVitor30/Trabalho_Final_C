all:  
    gcc -o teste.e main.o funcoes.o


main.o: main.c
    gcc -o main.o -c main.c

funcoes.o: funcoes.c
    gcc -o funcoes.o -c funcoes.c

clean:
    rm -f *.o prog.e  