#! /bin/bash

read -p 'Give me a number: ' n


#Factorial
m=1

if [ $n -eq 0 ]
then
  echo "$n!= 1"
else
  for (( i=1; i<=n; i++ ))
  do
    m=$(( m * i ))
  done
  echo "$n!= $m"
fi


#Check prime
i=2
f=0

while [ $i -le $(( n / 2 )) ]
do

  if [ $(( n % i )) -eq 0 ]
  then
    f=1
  fi

  (( i++ ))
done

if [ $f -eq 1 ]
then
  echo "$n is not prime"
else
  echo "$n is prime"
fi


#GCD
echo
read -p 'Give me a second number to find the GCD: ' b

if [ $b -lt $n ]
then
  m=$b
else
  m=$n
fi

j=0

while [ $m -ne 0 ]
do
  x=$(( n % m ))
  y=$(( b % m ))

  if [ $x -eq 0 ] && [ $y -eq 0 ]
  then
    echo "The GCD of $n and $b is $m"
    j=1
    break
  fi

  (( m-- ))
done
echo

#2^n
COUNTER=0
EXP=1
while [ $COUNTER -lt $n ]
do
    EXP=$(( EXP * 2 ))
    COUNTER=$(( COUNTER + 1 ))
done
echo "Expontential of $n is: $EXP"

#Fibonacci
declare -a arr
arr[0]=0
arr[1]=1

for (( i=2; i<n; i++ ))
do
arr[i]=$(( arr[i-1] + arr[i-2] ))
done

echo "The Fibonacci number for n=$n is ${arr[n-1]}"





