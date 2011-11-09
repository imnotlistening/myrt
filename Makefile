#
# (C) Copyright 2011
# Alex Waterman <imNotListening@gmail.com>
#
# myrt is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# myrt is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with myrt.  If not, see <http://www.gnu.org/licenses/>.
#
# Build the ray tracer.
#

include config.mk

# Set the build directory
export BUILD := $(PWD)

all:
	$(MAKE) -C src

clean:
	$(MAKE) -C src clean
