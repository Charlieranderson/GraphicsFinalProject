# GraphicsFinalProject

A note on how things are structured:

OLD STUFF:
- Most of the code in rend.cpp is what is expected, based on the homeworks, with a couple 
helper functions. I did expand rend.h a little to allow variable access.

- There are two other classes I added: LineEquations and MatrixEquations. They deal with 
what you would expect, and handle a lot of the recurring calculations. They can very likely 
be reused for our project with little to no modifications.

NEW STUFF:
- New struct in Gz called Tridata, used for storing converted Tris (now in worldspace)
- New pointer for Tridata buffer in rend.h, awaiting allocation in Renderer constructor
- New functions as part of the rend class called ConvertTri (Should be called in app), RayCast (called in RenderImg), RenderImg (The general call to render). The function comments are in rend.h.
- New function to construct Xwi


REMOVED:
-Xsp from rend class
-Removed contents of BeginRenderer, added in ConstructXwi, currently doesn't do anything. But we didn't need the transformations that were there before.


Notes: 
- We are going to need to reorganize the app a little to 1) convert the tri data to world space and stored in the renderer to be accessed during rendering and 2) convert the app data, like the lights and camera to world space as well.