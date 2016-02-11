g++ -std=c++11 TTT9Board.cpp Board.cpp
rm scripts/a.out
rm scripts2/b.out
cp a.out scripts/
cp a.out scripts2/
mv scripts2/a.out scripts2/b.out
./b.out

