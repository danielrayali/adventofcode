programs = d1s1

all: $(programs) gitignore

$(programs): %: %.cc
	g++ -std=c++17 -o $@ $<

gitignore:
	echo $(programs) > .gitignore
	git add ./.gitignore

clean:
	rm -rf $(programs)
