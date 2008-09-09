include definitions.mk
FILES := $(shell ls *.c *.S )
OBJECTS := $(subst .S,.o,$(subst .c,.o,$(FILES)))


all: $(OBJECTS)
