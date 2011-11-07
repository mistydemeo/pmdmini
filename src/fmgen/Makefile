include ../mak/config.mak

AR = ar
RANLIB = ranlib
CXX = g++
CC = gcc
TARGET = libfmgen.a

OBJDIR = obj

SRCS = file.cpp fmtimer.cpp opna.cpp \
fmgen.cpp opm.cpp psg.cpp

OBJS = $(addprefix $(OBJDIR)/,$(SRCS:.cpp=.o))

all : $(OBJDIR) $(TARGET)

$(TARGET) : $(OBJS)
	$(AR) rc $@ $(OBJS)
	$(RANLIB) $@

$(OBJDIR) : 
	@echo "Creates object directory..."
	@mkdir $(OBJDIR)

$(OBJDIR)/%.o : %.cpp
	$(CXX) $(CFLAGS) -o $@ $<

clean :
	rm -r $(OBJDIR)
	rm $(TARGET)

