.PHONY : default_target
default_target: all

PROJECT=?ch1

.PHONY : clear
clear:
	rm -f $(PROJECT)/CMakeCache.txt

.PHONY : all
all:
	cd $(PROJECT) && cmake .
	cd $(PROJECT) && make
	./$(PROJECT)/main