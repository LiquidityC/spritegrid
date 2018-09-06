all:
	@make -sC build
.PHONY: all

clean:
	@make clean -sC build
.PHONY: clean

test:
	@make test -sC build
.PHONY: test

run: $(all)
	@./build/spritegrid
.PHONY: run

lint:
	@make lint -sC build
.PHONY: lint
