programs = d1s1 d1s2 \
	d2s1 d2s2 \
	d3s1 d3s2 \
	d4s1 d4s2 \
	d5s1 d5s2 \
	d6s1 d6s2 \
	d7s1

all: $(programs) gitignore

$(programs): %: %.cc
	clang++ -std=c++17 -O0 -g -o $@ $<

gitignore:
	echo $(programs) > .gitignore
	git add ./.gitignore

clean:
	rm -rf $(programs)
