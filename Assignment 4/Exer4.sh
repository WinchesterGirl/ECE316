#!/bin/bash

start=2
end=$(( $# - 1))

for i in $( eval echo {$start..$end} )
do

    grep --color $argument${!i} ${!#}
done
