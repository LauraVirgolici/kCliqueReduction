IN=tests/in/$(CTG)/test$(TEST).in
OUT=tests/out/$(CTG)/test$(TEST).out
AUX=tests/aux/$(CTG)/test$(TEST).aux

build:
	gcc kCliqueBKT.c -o kCliqueBKT
	gcc kCliqueReduction.c -o kCliqueReduction

run_backtracking:
	./kCliqueBKT $(IN) > $(OUT)

run_reduction:
	./kCliqueReduction $(IN) > $(AUX)

clean:
	rm -rf kCliqueBKT kCliqueReduction
