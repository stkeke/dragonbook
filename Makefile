postfix: postfix.cpp
	g++ -o $@ $<

clean:
	rm -rf postfix
