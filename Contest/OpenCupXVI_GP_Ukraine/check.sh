for((;;))
do
    ./gen > in
    ./a.out < in > out1
    ./bf < in > out2
    diff out1 out2 || break
done
