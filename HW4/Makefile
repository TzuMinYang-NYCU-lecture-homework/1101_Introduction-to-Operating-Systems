all: 1_1 1_2 2

.PHONY: 1_1 1_2 2 clean

1_1:
	g++ -Wall -g -o ./src/hw4_1_1 ./src/hw4_1_1.cpp -lpthread
	./src/hw4_1_1 < ./test_case/input/12000-1.txt > ./test_case/output/12000-1-output.txt
	-diff -w -b -B ./test_case/solution/ans.txt ./test_case/output/12000-1-output.txt
	cat ./test_case/output/12000-1-output.txt
	@echo "\n=========================================================================\n"

1_2:
	g++ -Wall -g -o ./src/hw4_1_2 ./src/hw4_1_2.cpp -lpthread
	./src/hw4_1_2 < ./test_case/input/12000-2.txt > ./test_case/output/12000-2-output.txt
	-diff -w -b -B ./test_case/solution/ans.txt ./test_case/output/12000-2-output.txt
	cat ./test_case/output/12000-2-output.txt
	@echo "\n=========================================================================\n"

2:
	g++ -Wall -g -o ./src/hw4_2   ./src/hw4_2.cpp   -lpthread
	./src/hw4_2  < ./test_case/input/pi.txt > ./test_case/output/4_2-output.txt
	cat ./test_case/output/4_2-output.txt
	@echo "\n=========================================================================\n"

clean:
	rm ./src/hw4_1_1 ./src/hw4_1_2 ./src/hw4_2 ./test_case/output/12000-1-output.txt ./test_case/output/12000-2-output.txt ./test_case/output/4_2-output.txt