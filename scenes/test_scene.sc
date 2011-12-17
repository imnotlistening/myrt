#
# A test scene. '#' denotes comments. Empty lines are ignored. 
#

#
# Define some info for the ray tracer, i.e viewing location, screen size, etc.
#
# view <vec:location>
#   Defines the lolcation from which all rays originate. The direction of view
#   is always towards the origin.
# fov <degrees>
#   Specifies how big the field of view is in degrees.
# width <width>
# height <height>
#   The width/height in pixels. These should be integers.
#
view   [ 0 0 40 ]
fov    90
width  1800
height 900 

#
# You can put one object per line. The folling built in objects are available:
#
#   sphere <vec:origin> [radius] [vec:color]
#   plain  <vec:normal> <distance> [vec:color] [width] [length]
#   light  <vec:origin> <intensity> [radius] [decay]
#
# If a peice of data has vec: before it, then that means it must be a vector.
# Vectors are defined as follows: [ x y z ] where x, y, and z can be any
# combination of floats or integers. Integers will be converted to floats on
# load.
#
# Optional arguments are optional since they have defaults if left unspecified.
# If you wish to specify an optional argument, then *all* preceding optional
# arguments must also be specified. For instance, in order to specify the color
# of a spehere, you must also specify the radius.
#
# The color vector should have elements that exist in [0, 255].
#
# Here are some examples.
sphere [ 10 0 0 ]
sphere [ 0 10 0 ] 4
sphere [ 0 0 10 ] 4 [ 0 0 255 ]

# An XZ plane centered at default location: [0 0 0] of size 20x20.
plane  [ 0 1 0 ] 0 [ 255 0 0 ] 20 20

#[ 1.0 10.5 88 ]
#[ 1.0 10 88 ]
#[ 1 0 88.0 ]
#[ 1.0 10 88 ]
