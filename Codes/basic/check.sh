for ((i = 0; i < 100; i++))
do
    ./gen > in
    ./ac < in > out1
    ./tle < in > out2
    diff out1 out2 || break
done
