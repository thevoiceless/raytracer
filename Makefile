OPT = -O2
OBJS = Image.o IOstuff.o Vector.o raytrace.o
CPPS = Image.cpp IOstuff.cpp Vector.cpp  raytrace.cpp

all: raytrace

raytrace: objects $(OBJS)
	g++ $(OBJS) $(OPT) -o raytrace

objects: $(CPPS)
	g++ -c $(CPPS)

clean: 
	rm raytrace
	rm $(OBJS)
	rm *.ppm