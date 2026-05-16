demo:
	mkdir -p build/
	gcc -o build/demo demo.c src/kadane.c src/loop.c

debug:
	mkdir -p build/
	gcc -o build/tensor test/tensor.c src/loop.c

clean:
	rm -rf build/
