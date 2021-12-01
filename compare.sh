gen=""
prog=()

for (( i=0; i<=$#; i++ ))
do
	ag="${!i}"
	if [ "$ag" = "--generator" ] || [ "$ag" = "--gen" ] || [ "$ag" = "-g" ]; then
		if [ $i -ge $# ]; then
			echo "missing argument after '$ag'"
			exit
		fi
		((i=i+1))
		gen="${!i}"
	elif [ $i -gt 0 ]; then
		prog+=( "$ag" )
	fi
done

trap "exit" INT
test_cnt=0
while true
do
	((test_cnt=test_cnt+1))
	echo "running #$test_cnt"
	./"$gen" > in_
	if [ $? -ne 0 ]; then
		echo "generator '$gen' had non-zero return value ($?)"
		exit
	fi
	./"${prog[0]}" < in_ > out0_
	if [ $? -ne 0 ]; then
		echo "target '${prog[0]}' had non-zero return value ($?)"
		exit
	fi
	./"${prog[1]}" < in_ > out1_
	if [ $? -ne 0 ]; then
		echo "target '${prog[1]}' had non-zero return value ($?)"
		exit
	fi
	if ! cmp --silent -- "out0_" "out1_"; then
		echo "found diff"
		exit
	fi
	if [ $test_cnt -eq 1000 ]; then
		exit
	fi
done

rm in_ out0_ out1_
