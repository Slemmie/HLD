echo "tests: n < 100"
rm ./tests/n_less_100/*
for (( i=0; i<=10; i++ ))
do
	./gen 100 > "tests/n_less_100/test_$i"
done

echo "tests: n < 1000"
rm ./tests/n_less_1000/*
for (( i=0; i<=10; i++ ))
do
	./gen 1000 > "tests/n_less_1000/test_$i"
done

echo "tests: n < 10000"
rm ./tests/n_less_10000/*
for (( i=0; i<=10; i++ ))
do
	./gen 10000 > "tests/n_less_10000/test_$i"
done

echo "tests: n < 100000"
rm ./tests/n_less_100000/*
for (( i=0; i<=10; i++ ))
do
	./gen 100000 > "tests/n_less_100000/test_$i"
done

echo "tests: n < 1000000"
rm ./tests/n_less_1000000/*
for (( i=0; i<=10; i++ ))
do
	./gen 1000000 > "tests/n_less_1000000/test_$i"
done
