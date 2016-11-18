test

test -e

test -f

test -d

test -5

touch hi.txt

test -e hi.txt

test -e hi.txt && echo real

test -e hi.txt || echo real

test -d hi.txt && echo real

test -d hi.txt || echo real

test -f hi.txt && echo real

test -f hi.txt || echo real

test -e hi.txt; test -e hi.txt

test -e hi.txt; ls

ls; test -e hi.txt

ls; test -e hi.txt && echo real

test       -e hi.cpp 

test       -e             hi.cpp 

mkdir ashell; test -d ashell && echo real

test -e ashell

test -e ashell && echo real

test -e ashell || echo real

test -d ashell && echo real

test -d ashell || echo real

test -f ashell && echo real

test -f ashell || echo real

test -poop hi.txt

test -poop                hi.txt

test          -poop hi.txt

[ -e hi.txt ]

[ hi.txt]

[ -e hi.txt ] && echo real

[ hi.txt ] && echo real

[ -e ashell ]

[ -e ashell ] && echo real

[ -e ashell ] || echo real

[ -d ashell ]

[ -d ashell ] && echo real

[ -d ashell ] || echo real

[ -f ashell ]

[ -f ashell ] && echo real

[ -f ashell ] || echo real

[ -d ashell ]

[ -d ashell ] && echo real

[ -d ashell ] || echo real

[ -e hi.txt ]; [ -d ashell ]

[ -e hi.txt ] && [ -d ashell ]

[ -e hi.txt ] || [ -d ashell ]

[ -poop hi.txt ]

[ -f                    ashell ];        ls;   pwd

[ -f                    ashell ];  ls;   pwd



