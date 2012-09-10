OPT = -O2
OBJS = Material.o Image.o Vector.o Sphere.o Triangle.o IOstuff.o raytrace.o
CPPS = Material.cpp Image.cpp Vector.cpp Sphere.cpp Triangle.cpp IOstuff.cpp raytrace.cpp
EXES = raytrace

all: raytrace

raytrace: objects $(OBJS)
	g++ $(OBJS) $(OPT) -o raytrace

objects: $(CPPS)
	g++ -c $(CPPS)

clean: 
	rm $(EXES)
	rm $(OBJS)
	rm *.ppm