all:
	@make -sC build/debug
.PHONY: all

clean:
	@make clean -sC build/debug
	@make clean -sC build/release
.PHONY: clean

test:
	@make test -sC build/debug
.PHONY: test

run: $(all)
	@./build/debug/spritegrid
.PHONY: run

install:
	@make install -sC build/release
.PHONY: install

lint:
	@make lint -sC build/debug
.PHONY: lint
