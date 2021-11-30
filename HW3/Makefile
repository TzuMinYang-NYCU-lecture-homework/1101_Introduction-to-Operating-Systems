all:
	g++ -Wall -g -o 0816147_ST ./code/0816147_ST.cpp
	g++ -Wall -g -o 0816147_MT_best ./code/0816147_MT_best.cpp -lpthread
	g++ -Wall -g -o 0816147_MT_worst ./code/0816147_MT_worst.cpp -lpthread

	time ./0816147_MT_best < test/input/input_test.txt > test/output/output_test_MT_best.txt
	time ./0816147_MT_worst < test/input/input_test.txt > test/output/output_test_MT_worst.txt
	time ./0816147_ST < test/input/input_test.txt > test/output/output_test_ST.txt

	time ./0816147_MT_best < test/input/input1.txt > test/output/output1_MT_best.txt
	diff test/answer/answer1.txt test/output/output1_MT_best.txt
	time ./0816147_MT_worst < test/input/input1.txt > test/output/output1_MT_worst.txt
	diff test/answer/answer1.txt test/output/output1_MT_worst.txt	
	time ./0816147_ST < test/input/input1.txt > test/output/output1_ST.txt
	diff test/answer/answer1.txt test/output/output1_ST.txt

	time ./0816147_MT_best < test/input/input2.txt > test/output/output2_MT_best.txt
	diff test/answer/answer2.txt test/output/output2_MT_best.txt
	time ./0816147_MT_worst < test/input/input2.txt > test/output/output2_MT_worst.txt
	diff test/answer/answer2.txt test/output/output2_MT_worst.txt
	time ./0816147_ST < test/input/input2.txt > test/output/output2_ST.txt
	diff test/answer/answer2.txt test/output/output2_ST.txt	

	time ./0816147_MT_best < test/input/15w_input.txt > test/output/15w_output.txt
	diff  test/answer/15w_output.txt test/output/15w_output.txt -w
	time ./0816147_MT_worst < test/input/15w_input.txt > test/output/15w_output.txt
	diff  test/answer/15w_output.txt test/output/15w_output.txt -w
	time ./0816147_ST < test/input/15w_input.txt > test/output/15w_output.txt
	diff  test/answer/15w_output.txt test/output/15w_output.txt -w

	time ./0816147_MT_best < test/input/25w_input.txt > test/output/25w_output.txt
	diff  test/answer/25w_output.txt test/output/25w_output.txt -w
	time ./0816147_MT_worst < test/input/25w_input.txt > test/output/25w_output.txt
	diff  test/answer/25w_output.txt test/output/25w_output.txt -w
	time ./0816147_ST < test/input/25w_input.txt > test/output/25w_output.txt
	diff  test/answer/25w_output.txt test/output/25w_output.txt -w
