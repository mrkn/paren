all: build

build:
	@$(MAKE) $(MAKEFLAGS) $(TARGET:src/%=%) -C src

clean:
	@$(MAKE) $(MAKEFLAGS) clean -C src

test: build
	@./test.sh || :
