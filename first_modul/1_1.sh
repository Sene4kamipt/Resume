#!/usr/bin/env bash

declare -A matrix
_number_of_raws=0
_current_raw=0
while read line
do
  IFS="",
  _current_column=0
  for element in $line
  do
    matrix[$_current_raw,$_current_column]=$element
    _current_column=$(( $_current_column + 1 ))
  done
  _current_raw=$(( $_current_raw + 1 ))
done < $1
_number_of_raws=$_current_raw

function solute {
  current_raw=0;
  i=0;j=0;nulli='0';
  current_column=0
  while [ $current_raw -lt $_number_of_raws ]
  do
    k=$current_raw
    while [[ 1 -eq $( echo "$k<$_number_of_raws" | bc -l ) ]]
    do
    if [[ 1 -eq $( echo "${matrix[$k,$current_column]}==$nulli" | bc -l ) ]]
    then
      k=$(( $k + 1 ))
      #echo "kwkdw $k"
    else
      break
    fi
    done
    q=0
    while [ $q -le $_number_of_raws ]
    do
      helpv=${matrix[$current_raw,$q]}
      matrix[$current_raw,$q]=${matrix[$k,$q]}
      matrix[$k,$q]=$helpv
      q=$(( $q + 1 ))
      #echo "kodsokd $helpv" 
    done
    #i=0;j=0;helpv=$(( $_number_of_raws - 1 ));
    #while [ $i -lt $_number_of_raws ]
    #do
      #j=0
      #while [ $j -lt $(($_number_of_raws+1)) ]
      #do
        #echo ${matrix[$i,$j]}
        #j=$(($j + 1))
      #done
      #i=$(($i + 1))
    #done

    i=0
    while [ $i -lt $current_raw ]
    do
      #echo hui1
      quotient=`echo "${matrix[$i,$current_column]} / ${matrix[$current_raw,$current_column]}" | bc -l`
      #echo hui2
      j=$current_column
      while [ $j -le $_number_of_raws ]
      do
        matrix[$i,$j]=`echo "${matrix[$i,$j]} - (${matrix[$current_raw,$j]} * $quotient)" | bc -l`
        j=$(( $j + 1 ))
      done
      i=$(( $i + 1 )) 
    done
    i=$(( $current_raw + 1 ))
    #echo "passed till current raw"
    while [ $i -lt $_number_of_raws ]
    do
      #echo "hui1 $_number_of_raws"
      quotient=`echo "${matrix[$i,$current_column]} / ${matrix[$current_raw,$current_column]}" | bc -l`
      #echo hui2
      j=$current_column
      while [ $j -le $_number_of_raws ]
      do
        matrix[$i,$j]=`echo "${matrix[$i,$j]} - (${matrix[$current_raw,$j]} * $quotient)" | bc -l`
        j=$(( $j + 1 ))
      done
      i=$(( $i + 1 ))
    done
    current_column=$(( $current_column + 1 ))
    current_raw=$(( $current_raw + 1 ))
    #echo "raw done"      
  
  done
  i=0;j=0;helpv=$(( $_number_of_raws - 1 ));
  while [ $i -lt $_number_of_raws ]
  do
    answer=`echo "${matrix[$i,$_number_of_raws]}/${matrix[$i,$i]}" | bc -l`
    #j=0
    #while [ $j -lt $(($_number_of_raws+1)) ]
    #do
      #echo ${matrix[$i,$j]}
      #j=$(($j + 1))
    #done
    echo $answer
    i=$(($i + 1))
  done
}

declare -A matrix
solute
