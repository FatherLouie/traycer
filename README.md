# Ray Tracing

This is a project to build a basic ray tracer to render simple images and scenes based on user input.

## Description

The current code can render spheres of 3 different materials- matte (lambertian), metal, and glass (any dielectric in general). In the [main file](https://github.com/FatherLouie/traycer/blob/main/zimage.cpp), the user can specify the position, size and material of each sphere in the scene. The user has control over the image resolution, camera position, and camera lens properties that must be specified before rendering the scene. 

## Project Files

### [vec3.h](https://github.com/FatherLouie/traycer/blob/main/vec3.h)

This is a class that simulates a 3 component vector. Standard mathematical operations on vectors have been implemented here. This class goes by two aliases, point and colour, to differentiate the two uses of the same class in the code.

### [colour.h](https://github.com/FatherLouie/traycer/blob/main/colour.h)

This file contains methods on the vec3 class that are specific to the vec3's functionality of storing the 3 components of a colour, r, g, and b values. This file contains the gamma correction constant (which determines how colour is displayed on screens) and the mapping form linear space to the desired gamma space. 

### [ray.h](https://github.com/FatherLouie/traycer/blob/main/ray.h)

This file implements the ray class, a geometrical object with an origin and a direction (which are both of type vec3).

### [interval.h](https://github.com/FatherLouie/traycer/blob/main/interval.h)

Contains the class interval, which is equivalent to an interval between two numbers. Basic functions that check if a number lies in the interval are implemented. Two constants, the universal interval spanning all reals and the empty interval are defined.

### [record.h](https://github.com/FatherLouie/traycer/blob/main/record.h)

Deifnes a class that contains all relevant information when a ray hits an object in our scene. A null record is also defined, in case the ray does not hit any object.

### [polygon.h](https://github.com/FatherLouie/traycer/blob/main/polygon.h)

Two classes, polygon and circle have been implemented. Each have functions thaty determine of an arbitrary point lies inside or outside the shape.<br/>
**Polygon:** Defined by the normal to the plane in which it lies, the number of sides it has, and an arbitrary point in its interior, say its centroid. We can then define the polygon by adding appropriate number of verices. A regular polygon can also be generated given one vertex to start from.
**Circle:** Defined by the plane in which it lies, its centre and radius.

### [hittables.h](https://github.com/FatherLouie/traycer/blob/main/hittables.h)

Defines a superclass hittable, from which subclasses representing objects with varying geometries in the scene can be derived. Whenever a ray hits a hittable, a record is generated containing the necesssary details.<br/><br/>

  ***Sphere:** Implements the sphere, with the math required to calculate the boundaries of the sphere and reflect the rays appropriately.<br/>
  ***Cylinder:** Implements a finite length cylinder, with calculations regarding the two flat faces and the curved face done separately.<br/>
  ***Cone:** Implements a finite length cone, with the lateral and base faces treated separately. Both the cylinder and cone use the circle class.<br/>
  ***Prism:** Implements the prism, where any polygon can be defined as the base and a parallel face would be the top. Lateral faces are rectangular.<br/>
  ***Pyramid:** Implements the pyramid, with any polygon as the base and a point where the triangular lateral faces meet.<br/>

### [materials.h](https://github.com/FatherLouie/traycer/blob/main/materials.h)

Defines a superclass material, which implements reflection and refraction that derived materials can inherit. The virtual scatter function is separately defined for each material, to calculate the scattered ray given the incident. The emit function associated with each material determines if the source emits light.<br/><br/>
**Lambertian:** simulates a matte finish, with the scatter function implemented to reutrn rays in all directions.<br/>
**Metal:** Has an additional property fuzz, that indicates the smoothness of the metal finish, with 0 for perfectly smooth, and 1 for the opposite. <br/>
**Dielectric:** Has the property refractive_index, which deals with ray scattering when the medium changes and light refracts.<br/>
**Emitter:** Simulates a light source by giving off light of the specified colour.

### [camera.h](https://github.com/FatherLouie/traycer/blob/main/camera.h)

Contains the implementation of the camera. Has properties that define the image resolution, apsect ratio, camera position in the scene, it's field of view, and lens specifications like the depth of field and focal length. All of these parameters can be changed from outside the class, and more specifically they are set in the [main file](https://github.com/FatherLouie/traycer/blob/main/zimage.cpp).<br/><br/>
The camera also sets up the viewport with appropriate dimensions for viewing the scene and sending appropriate rays to each pixel.<br/><br/>
The render function puts all the pieces together to output the desired scene. Redirecting the output to a `.ppm` file enables the creation of the image.

### [utilities.h](https://github.com/FatherLouie/traycer/blob/main/utilities.h) & [classes.h](https://github.com/FatherLouie/traycer/blob/main/classes.h)

Important C++ libraries and created classes included here to avoid multiple inclusions in every file.
