JAVAC=javac
JAVA=java

.PHONY: all run clean

all: ProfilerTarget.class

ProfilerTarget.class: ProfilerTarget.java
	$(JAVAC) $<

run: ProfilerTarget.class
	$(JAVA) ProfilerTarget 120

clean:
	rm -f *.class async-*.html async-*.jfr
