include ../mak/config.mak

TARGET = libpmdwin.a

OBJDIR = obj

SRCS = \
opnaw.cpp \
p86drv.cpp \
pmdwin.cpp \
ppsdrv.cpp \
ppz8l.cpp \
table.cpp \
util.cpp


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