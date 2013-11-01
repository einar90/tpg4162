LIBPATH = -L./
LDFLAGS = -lGL -lGLU -lglut

CFLAGS = 
RM = rm
PROJ = glsl
# add here additional object files
OBJS = main.o GLee.o  

all: $(PROJ)

$(PROJ): $(OBJS)
	$(CC) $(LIBPATH) -o $@ $(OBJS) $(LDFLAGS) -L/usr/lib64 -lstdc++

%.o: %.c
	$(CC) $(INCPATH) $(CFLAGS) -c $*.c

%.o: %.cpp
	$(CC) $(INCPATH) $(CFLAGS) -c $*.cpp

clean:
	$(RM) *.o
	$(RM) $(PROJ)
