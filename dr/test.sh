#! /bin/sh

RUNS_PER_N=${RUNS_PER_N:-1000}
DR_ARG=${DR_ARG:-d10}
N_RANGE="1 2 3 4 5 6 7 8 9 10"

for N in $N_RANGE
do
	RUN_NO=1
	NUM_NS=0
	while [ $RUN_NO -lt $RUNS_PER_N ]
	do
		DIE=$(./dr $DR_ARG)
		if [ $DIE -eq $N ]
		then
			NUM_NS=$(( $NUM_NS + 1 ))
		fi
		RUN_NO=$(( $RUN_NO + 1 ))
	done

	echo "in $RUNS_PER_N rolls: $NUM_NS occurences of $N"
done
