all:
	dos2unix *.ml
	dos2unix *.rb
	chmod 644 *.ml
	chmod 755 *.rb
	mkdir -p student_outputs
	rm -f student_outputs/*
	cp rube.ml build
	cd build; make
	cp build/rube .

clean:
	cd build; make clean
	cd ..
	rm build/rube.ml
	rm -f student_outputs/*
	rm rube
