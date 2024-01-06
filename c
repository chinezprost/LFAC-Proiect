clear 
rm -f lex.yy.c
rm -f y.tab.c
rm -f p1
bison -d p1.y
lex p1.l

g++ -w lex.yy.c p1.tab.c -o p1

./p1 input.txt