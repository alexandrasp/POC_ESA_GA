all: telosb_serial_msg.java sbt80_serial_msg.java

telosb_serial_msg.java: telosb_serial_msg.h
	@mig java -java-classname=blah.foo.$(@:.java=) $< $(@:.java=) -o $@
	@javac -source 1.4 -target 1.4 $@

sbt80_serial_msg.java: sbt80_serial_msg.h
	@mig java -java-classname=blah.foo.$(@:.java=) $< $(@:.java=) -o $@
	@javac -source 1.4 -target 1.4 $@

clean:
	@rm -f *.java *.class
