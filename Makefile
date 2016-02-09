# *-* makefile *-*
.PHONY:all clean

platform := ${shell uname}

ifeq (platform,Darwin)
  flags := -shared -fPIC -std=c++11
else
  flags := -shared -undefined dynamic_lookup -fPIC -std=c++11
endif

libs := -lc++ -lfolly
src := src/buildkit.cpp
lib := buildkit.so

all:
	@clang++ ${flags} ${src} ${libs} -o ${lib}

example:all
	@make -C example

clean:
	@rm -rf *.o *.so
