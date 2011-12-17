#
# A very simple test scene.
#

view    [ 0 50 160 ]
#view    [ 0 0 150 ]
fov     65
width   1200
height  800
density 5
ambience  0.1
aaliasing 16

# Specify the model to use.
model   ray-trace

# A sphere.
sphere [ -10 20 0 ] 8 [ 0 0 255 ]
sphere [ 10 20 0 ] 8 [ 0 255 0 ]
#sphere [ 25 0 0 ] 30 [ 0 255 0 ]

# A plane.
plane  [ 0 1 0 ] 0 [ 150 230 255 ] 65 65

# Finally, a light source.
#light  [ 0 10000 0 ] 1 100
#light [  20 40 -40 ] 1 4
#light [ -20 40 -40 ] 1 4
light [ 40 6 40 ] 1 1
light [ 140 140 -140 ] 0.1 16