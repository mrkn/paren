TARGET = src/paren

all: $(TARGET)

$(TARGET):
	@$(MAKE) $(MAKEFLAGS) $(TARGET:src/%=%) -C src

clean:
	@$(MAKE) $(MAKEFLAGS) clean -C src

test: $(TARGET)
	@./test.sh || :
