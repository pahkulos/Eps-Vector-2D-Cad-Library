target:	test_program

test_program:	main.c CAD2D.h CAD2D.c 
		gcc main.c CAD2D.c -lm -o test
		./test

