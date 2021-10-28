#!/bin/bash

./hw2-1 < Test\ cases/Q1.txt > myA1.txt 
./hw2-2 < Test\ cases/Q2.txt > myA2.txt 
./hw2-3 < Test\ cases/Q3.txt > myA3.txt 
./hw2-4 < Test\ cases/Q4.txt > myA4.txt

echo "----------------------------------------------------------------------"
diff --strip-trailing-cr myA1.txt Test\ cases/A1.txt 

echo "----------------------------------------------------------------------"
diff --strip-trailing-cr myA2.txt Test\ cases/A2.txt 

echo "----------------------------------------------------------------------"
diff --strip-trailing-cr myA3.txt Test\ cases/A3.txt 

echo "----------------------------------------------------------------------"
diff --strip-trailing-cr myA4.txt Test\ cases/A4.txt 

exit 0
