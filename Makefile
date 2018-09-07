TARGET = paren

$(TARGET):
	@(echo '#! /bin/sh'; echo 'echo nil';) > $(TARGET)
	@chmod 755 $(TARGET)

test: $(TARGET)
	@./test.sh || :

clean:
	@rm -f $(TARGET)
