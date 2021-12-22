programs = d1s1 d1s2 \
	d2s1 d2s2 \
	d3s1

all: $(programs) gitignore

$(programs): %: %.cc
	clang++ -std=c++17 -o $@ $<

gitignore:
	echo $(programs) > .gitignore
	git add ./.gitignore

clean:
	rm -rf $(programs)
