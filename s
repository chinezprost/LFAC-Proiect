
rm -f lex.yy.c
rm -f y.tab.c
rm -f X
bison -d X.y
lex X.l

g++ -w lex.yy.c X.tab.c -o X

./X input.txt