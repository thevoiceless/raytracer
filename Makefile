OPT = -O2
OBJS = Image.o Vector.o Sphere.o IOstuff.o raytrace.o
CPPS = Image.cpp Vector.cpp Sphere.cpp IOstuff.cpp raytrace.cpp

all: raytrace

raytrace: objects $(OBJS)
	g++ $(OBJS) $(OPT) -o raytrace

objects: $(CPPS)
	g++ -c $(CPPS)

clean: 
	rm raytrace
	rm $(OBJS)
	rm *.ppm