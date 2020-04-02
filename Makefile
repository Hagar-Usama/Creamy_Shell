CC= g++
CN= 
RUN=./
TARGET= shell

compile:
	echo "Compiling ..."
	$(CC) -Wall $(CN) -o $(TARGET) $(TARGET).cpp
	$(RUN)$(TARGET)
run:
	echo "Runnig ..."
	$(RUN)$(TARGET)
greet:
	echo "Hello! Have a Creamy day 🍦!"

clean:
	 rm $(TARGET)

