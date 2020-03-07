for((i=0;;i++))
do
    echo $i
    ./gen > in
    ./wa < in > out1
    ./bf < in > out2
    diff out1 out2 || break
done
