LIB = libpmdmini.a

PMDMINI_DIR = src
FMGEN_DIR = src/fmgen
PMDWIN_DIR = src/pmdwin

FMGEN_CFLAGS = -I$(FMGEN_DIR)
PMDWIN_CFLAGS = -I$(PMDWIN_DIR)


SRCS_FMGEN = file.cpp \
 fmtimer.cpp \
 opna.cpp \
 fmgen.cpp \
 opm.cpp \
 psg.cpp


SRCS_PMDWIN = \
opnaw.cpp \
p86drv.cpp \
pmdwin.cpp \
ppsdrv.cpp \
ppz8l.cpp \
table.cpp \
util.cpp

SRCS_PMDMINI = pmdmini.c

SRCDIR = src
OBJDIR = obj

OBJS  = $(addprefix $(OBJDIR)/,$(SRCS_FMGEN:.cpp=.o))
OBJS += $(addprefix $(OBJDIR)/,$(SRCS_PMDWIN:.cpp=.o))
OBJS += $(addprefix $(OBJDIR)/,$(SRCS_PMDMINI:.c=.o))

all : $(OBJDIR) $(LIB)

$(OBJDIR) :
	mkdir $(OBJDIR)

$(LIB) : $(OBJS)
	$(AR) r $@ $(OBJS)

$(OBJDIR)/%.o : $(FMGEN_DIR)/%.cpp
	$(CXX) -o $@ $< -c $(FMGEN_CFLAGS) $(CFLAGS)

$(OBJDIR)/%.o : $(PMDWIN_DIR)/%.cpp
	$(CXX)  -o $@ $< -c $(FMGEN_CFLAGS) $(PMDWIN_CFLAGS) $(CFLAGS)

$(OBJDIR)/%.o : $(PMDMINI_DIR)/%.c
	$(CXX)  -o $@ $< -c $(FMGEN_CFLAGS) $(PMDWIN_CFLAGS) $(CFLAGS)


clean :
	rm -rf $(OBJDIR)
	rm -f $(LIB) 
