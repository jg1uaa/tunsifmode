TARGET = tunsifmode

$(TARGET): $(TARGET).c
	$(CC) -Wall -O2 $< -o $@

clean:
	rm -f $(TARGET)
