#!/usr/bin/env bash

size=1000;
arrayOrder=(A R D)
sortAlgorithm=( I S )
file=simulation.csv
totTime=0;

echo -n '' > $file
for algorithm in "${sortAlgorithm[@]}";do
    echo "SORTING ALGORITHM, SIZE, BEST, AVERAGE, WORST" >> $file;
    for (( size=1; size<=5000000000; size=size*2 ));do
        echo -n "$algorithm, $size, " >> $file
        #totTime=0;
        for order in "${arrayOrder[@]}";do
            if [ $size -gt 1000000 ];then
                if [ "$order" != "A" ] || [ "$algorithm" != "I" ];then
                    echo -n "NAN," >> $file
                    continue
                fi
            fi

            #echo "$size , $order"
            ( /usr/bin/time ./assign1.out -G $algorithm -N $size -S $order; ) 2>&1 | grep user |awk '{print $1}' | sed 's/[^0-9.]*//g'| tr -d '\n' >> $file
            echo -n ", " >> $file
            # for(( x=1; x<=10; x++ ));do #repeat the test 100 times and get the average time
            #     temp=$(( /usr/bin/time -f "%U" assign1.out -G $algorithm -N $size -S $order; ) 2>&1)
            #     totTime=$( echo "$temp + $totTime" | bc -l );
            #     #totTime = $((temp+totTime))
            # done
            # totTime=$( echo "$totTime/100" | bc -l );
            # echo $totTime >> $file
        done
        echo >> $file;
    done

    #done
    echo >> $file;
    echo >> $file;
   # do whatever on $i
done
