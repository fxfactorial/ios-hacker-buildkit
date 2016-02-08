
.PHONY:all clean

flags := -shared  -fPIC -std=c++11
libs := -lc++ -lfolly
src := theos.cpp
lib := theos.so

all:
	@clang++ ${flags} ${src} ${libs} -o ${lib}

example:all
	@make -C example

clean:
	@rm -rf *.{o,so}
