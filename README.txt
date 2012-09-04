
This is a skeleton code for the ray tracing project.
It contains a simple class for writing binary PPM files and
a skeleton for the function to read the input files.
Compile and run as described in the project description:
`make' in the Szymczak directory and then `./raytrace'.
The code requires an input file named input.txt to run 
(although it doesn't do anything with it except for 
scanning through it right now).

Here is an outline of what needs to be done to complete this
project.

(1) Design your datastructures for 3D vectors

Example:

class vector {
  public:
    double x,y,z;
};

vector add ( vector a, vector b )
{
  vector result;
  result.x = a.x+b.x;
  result.y = a.y+b.y;
  result.z = a.z+b.z;
  return result;
}

double dot ( vector a, vector b )
{
  return a.x*b.x+a.y*b.y+a.z*b.z;
}

etc.
If you know OO programming well, you can venture into 
implementing overloaded operators and other fun things,
but don't overdo: have the required content ready by the
deadlines!!!

(2) Design your datastructures for rays and primitives

Example:  [vectors and points are really the same beast,
           so we'll use the vector class to represent 3D points here]

class material {
  public:
    double k_diff_R,k_diff_G,k_diff_B;
    double k_ambient_R,k_ambient_G,k_ambient_B;
    double k_spec;
    double n_spec;
};

class ray {
  public:
    vector origin;
    vector direction;
};

class triangle {
  public:
    vector a1,a2,a3;
    material m;
};

class sphere {
  public:
    vector center;
    double radius;
    material m;
};

You can keep all the spheres and triangles in two different vectors. 
Again, there if you feel strong in OO programming, you can make it more
fun and, say, define a virtual primitive class with triangle and sphere
as descendants. But don't overdo or venture into it if you don't have 
experience.

(3) Build upon (1) and (2) to implement intersection routines.

Example:

double intersectionT ( ray r, triangle t )
{
[....]
}

double intersectionS ( ray r, sphere s )
{
[....]
}

in both cases, you can return the t-value corresponding to the intersection
if it exists and a negative number (say, -1) if there's no intersection.
In the sphere case, return the smaller t if there are two.

(4) Design a datastructure for storing the primitives. We'll keep things
simple here and just use a separate vector for all triangles and another
one for spheres. Thus, we'll have the following global variables:

triangle *T;
sphere *S;
int n_T,n_S;  // number of triangles and spheres

You can allocate T and S and fill them out at startup, when reading in the 
input file. The total number of primitives is one of the numbers in the 
header of the input file (number_of_primitives in the read_input_file
function). Once you read it, you can do
T = new triangle[number_of_prmitives];
S = new sphere[number_of_primitives];
and then fill the vectors with primitive information as they are read in 
the loop in the read_input_file function.

In what follows, we will refer to a primitive by an integer ID. 
The primitive with ID equal to pid is:
- triangle t[pid] if 0<=pid<n_T
- sphere s[pid-n_T] if n_T<=pid<n_T+n_S

(5) Blend the intersection functions into one:

double intersection ( ray r, int pid ) :
if pid<n_T then 
   return intersectT(r,T[pid])
else
   return intersectS(r,S[pid-n_T])

(6) Write a function for computing closest intersection point
with the primitives; make it return the t value for the intersection
(-1 if the ray misses all primitives) AND the pid of the 
primitive which contains the closest intersection point;
you can make a class that has a double t and an int pid
component the return type.

ClosestIntersection ( ray r ) :
double mint = -1; 
int pid;
for i:=0 to n_T+n_S-1 do:
  t := intersect(r,i);
  if t!=-1 and (mint==-1 or t<mint) then
     mint:=t;
     pid:=i;
  endif
endfor
return (mint,pid)

(7) Write a function for computing the eye ray for a pixel (i,j)

ray EyeRay ( int i, int j )

... type in the formula from the Assignments/Project 1/Center of a pixel writeup

(8) Now you have the necessary material for report #1.
Basically, do:

for ( x=0; x<resolution_x; x++ )
  for ( y=0; y<resolution_y; y++ )
    ray r = EyeRay(x,y);
    (t,pid) := ClosestIntersection(r);
    if (t==-1) then use 0,0,0 as the R,G and B values
       else use diffuse RGB components of MaterialOf(pid)
  endfor
endfor

where MaterialOf ( int pid ) is a function that returns the 
material of primitive with ID pid, i.e. does the following:
if pid<n_T then return T[pid].m else return S[pid-n_T].m;

-----------------------------------------------------------------------------

(9) Implement illumination 

For that, we need the normal vector, so let's implement it first.
p is a point on the primitive with ID pid. x is the cross product.

vector normal ( vector p, int pid ) :
if pid<n_T then
  // triangle case
  vector n0 = (T[pid].a3-T[pid].a1)x(T[pid].a2-T[pid].a1)
  // now we check if n0 points to the side containing viewpoint; if not, need to negate n0
  if n0[dot](e-T[pid].a1)>=0 then return n0 else return -n0;
else
  // sphere... we assume the origin of the ray is outside
  return p-S[pid-n_T].c
endif

For the illumination formula, we'll need the view and light vectors

vector VVector ( vector p ) :
return normalize(e-p)

vector LVector ( vector p ) :
return normalize(b-p)

Finally, implement the illumination formula. This one is with a test
for p being in the shadow of its own primitive. You may use the 
vector class to represent color (x,y,z = r,g,b components)
or define a separate color class.

color Illumination ( vector p, int pid )
n := normal(p,pid);
if (n[dot](b-p))<0 then
  // p in shadow of its primitive
  return the value of the Ambient term; use material properties returned by MaterialOf(pid) 
       -- see end of (8)
else
  N:= normalize(n);
  L:= LVector(p);
  V:= VVector(p);
  return value of the illumination formula; use material properties returned by 
       MaterialOf(pid)

(10) You are almost done with report #2: just add a call to the Illumination(..) function:

for ( x=0; x<resolution_x; x++ )
  for ( y=0; y<resolution_y; y++ )
    ray r = EyeRay(x,y);
    (t,pid) := ClosestIntersection(r);
    if (t==-1) then use 0,0,0 as the R,G and B values and continue
    p:= r.o + t*r.d;
    c:= Illumination(p,pid);
    use color c for the current pixel
  endfor
endfor

-----------------------------------------------------------------------------

(11) Add shadows

We already test if p is in shadow of its own primitive. All we need to do is
to include a test for being in shadow of any other primitive. Here is the 
pseudocode:

bool IsInShadow2 ( vector p, int pid )
// p is a point on primitive pid
// first compute the shadow ray
ray r (origin=p, direction=b-p)
for i:=0 to n_T+n_S do:
  if i!=pid then
     // don't want to use primitive containing p...
     t:= intersection(r,i);
     if t>=0 and t<=1 then return true;
  endif
endfor 
return false;

(12) You are almost done. Just include the full shadow test in the illumination function (end of (9)):

color Illumination ( vector p, int pid )
n := normal(p,pid);
if (n[dot](b-p))<0 or IsInShadow2(p,pid) then  // we added or IsInShadow2(p,pid) here
  // p in shadow of its primitive
  return the value of the Ambient term; use material properties returned by MaterialOf(pid) 
       -- see end of (8)
else
  N:= normalize(n);
  L:= LVector(p);
  V:= VVector(p);
  return value of the illumination formula; use material properties returned by 
       MaterialOf(pid)

-----------------------------------------------------------------------------

