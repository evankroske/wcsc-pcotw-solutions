all: Main.class

test: Main.class
	java Main < input

%.class: %.java
	javac $<

clean:
	rm -f *.class
