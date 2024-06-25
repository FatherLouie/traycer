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

### [hittables.h](https://github.com/FatherLouie/traycer/blob/main/hittables.h)

Defines a superclass hittable, from which subclasses representing objects in the scene can be derived.<br/><br/>
The hittable_list class is intended to hold all the hittables that are to be rendered.<br/><br/>
The sphere class implements the sphere, with the hit method calculating it's boundaries and generating a record when a ray hits a sphere.

### [materials.h](https://github.com/FatherLouie/traycer/blob/main/materials.h)

Defines a superclass material, which implements reflection and refraction that derived materials can inherit. The virtual scatter function is separately defined for each material, to calculate the scattered ray given the incident.<br/><br/>
The lambertian class simulates a matte finish, with the scatter function implemented to reutrn rays in all directions.<br/>
The metal class has an additional property fuzz, that indicates the smoothness of the metal finish, with 0 for perfectly smooth, and 1 for the opposite. <br/>
The dielectric class has the property refractive_index, which deals with ray scattering when the medium changes and light refracts.

### [camera.h](https://github.com/FatherLouie/traycer/blob/main/camera.h)

Contains the implementation of the camera. Has properties that define the image resolution, apsect ratio, camera position in the scene, it's field of view, and lens specifications like the depth of field and focal length. All of these parameters can be changed from outside the class, and more specifically they are set in the [main file](https://github.com/FatherLouie/traycer/blob/main/zimage.cpp).<br/><br/>
The camera also sets up the viewport with appropriate dimensions for viewing the scene and sending appropriate rays to eeach pixel. The render function puts all the pieces together to output the desired scene. Redirecting the output to a `.ppm` file enables the creation of the image.

### [utilities.h](https://github.com/FatherLouie/traycer/blob/main/utilities.h) & [classes.h](https://github.com/FatherLouie/traycer/blob/main/classes.h)

Important C++ libraries and created classes included here to avoid multiple inclusions in every file.
