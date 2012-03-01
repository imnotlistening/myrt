#
# A very simple test scene.
#

view		[ 0 60 160 ]
fov		65
width		1200
height		800
density		8
depth		4
ambience	0.1
aaliasing	4
threads		4
reflectance	0.3

# Specify the model to use.
model		ray-trace

# A sphere.
sphere [ -10 20 0 ] 8 [ 0 0 255 ]
sphere [ 10 20 0 ] 8 [ 0 255 0 ]

# A plane.
plane  [  0  1  0 ] 0   [ 150 255 255 ]
plane  [  1  0  0 ] -65 [ 150 255 255 ]
plane  [ -1  0  0 ] -65 [ 150 255 255 ]
plane  [  0  0  1 ] -65 [ 150 255 255 ]

# Finally, a light source.
light [ 10 40 40 ] 15 1 30

# Post processing effects.
post-process	glow