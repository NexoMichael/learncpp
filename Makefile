.PHONY : default_target
default_target: all

PROJECT=?ch1

.PHONY : all
all:
	cd $(PROJECT) && cmake .
	cd $(PROJECT) && make
	./$(PROJECT)/main