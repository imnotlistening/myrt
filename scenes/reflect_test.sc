#
# Test out reflectence in a simple manor.
#

view            [ 0 48 120 ]
fov             65
width           1200
height          800
density         8
depth           4
ambience        0.2
aaliasing       16
threads         4
reflectance     0.5

# Specify the model to use.
model           ray-trace

#
# Make a spere that is opaque for now.
sphere [ 10 20 0 ] 8 [ 255 0 0 ]

#
# A plane to sit under the sphere, hopefully picking up an image of the sphere.
plane  [ 0 1 0 ] 0   [ 150 255 255 ] 50 50

#
# A light source to give some illumination to the scene.
light [ 30 40 60 ] 15 1 30

# Make the light look better.
post-process    glow