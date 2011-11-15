#
# Makefile
#

include mak/general.mak

SRC_DIR = src
SRC_PMDDIR = $(SRC_DIR)/pmdwin

CFLAGS += -I$(SRC_DIR)
CFLAGS += -I$(SRC_PMDDIR)

SDL_LIBS = `sdl-config --libs`
SDL_CFLAGS = `sdl-config --cflags`

#
# definations for packing
#

TITLE = pmdmini
TARGET = pmdplay

FILES = Makefile Makefile.lib $(TITLE).txt 
FILES += sdlplay.c

FILES_ORG = inherits
LIB = lib$(TITLE).a

MAK_DIR = mak


ZIPSRC = $(TITLE)`date +"%y%m%d"`.zip
TOUCH = touch -t `date +"%m%d0000"`


OBJS   = sdlplay.o $(LIB)


all : $(TARGET)

$(TARGET) : $(OBJS)
	$(LD) $(LFLAGS) -o $@ $(OBJS) $(SDL_LIBS)

$(LIB):
	make -f Makefile.lib

%.o : %.c
	$(CXX) -o $@ $< -c $(CFLAGS) $(SDL_CFLAGS) 

clean :
	make -f Makefile.lib clean
	rm -f $(TARGET) $(OBJS)

dist :
	find . -name ".DS_Store" -exec rm -f {} \;
	find $(FILES) $(SRC_DIR) -exec $(TOUCH) {} \;
	find $(MAK_DIR) -exec $(TOUCH) {} \;
	
	rm -f $(ZIPSRC)
	zip -r $(ZIPSRC) $(MAK_DIR) $(SRC_DIR) $(FILES) $(FILES_ORG)

