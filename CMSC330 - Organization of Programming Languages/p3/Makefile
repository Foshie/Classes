# this shouldn't do anything since nothing needs to be compiled.

all:
	dos2unix *.ml
	dos2unix *.rb
	chmod 644 *.ml
	chmod 755 *.rb
	mkdir -p student_outputs
	chmod a+w ./student_outputs
	rm -f ./student_outputs/*

clean:
	rm -f *~
