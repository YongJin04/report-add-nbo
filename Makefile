all: run

thousand.bin:
	echo -n -e \\x00\\x00\\x03\\xe8 > thousand.bin

five-hundred.bin:
	echo -n -e \\x00\\x00\\x01\\xf4 > five_hundred.bin

run: thousand.bin five_hundred.bin
	./add_nbo thousand.bin five_hundred.bin

clean:
	rm -f thousand.bin five_hundred.bin add_nbo


