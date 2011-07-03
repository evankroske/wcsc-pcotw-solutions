all: Decode.class

%.class: %.java
	javac $<

%.java: %.java.template
	sed "s/$$CHARACTER_MAP$$/$$(ruby genkeymap.rb -n charMap < mapping)/" \
		< $< \
		> $@
