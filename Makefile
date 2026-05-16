demo:
	mkdir -p build/
	gcc -o build/demo demo.c src/kadane.c src/iter.c

debug:
	mkdir -p build/
	gcc -o build/tensor test/tensor.c src/iter.c

clean:
	rm -rf build/
