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
# Config for this project.
#

# If verbose is specified then turn on compiler messages.
ifeq ($(V), 1)
VERBOSE =
else
VERBOSE = @
endif

# Command definitions.
MAKE	:= @make --no-print-directory
CC	:= $(VERBOSE)gcc
LD	:= $(VERBOSE)gcc # Hehe, just use gcc.
LEX	:= $(VERBOSE)flex
MSG	:= @echo

# Set this for optimization levels. Useful during debugging when optimization
# is a real pain in the ass.
OPT	:= -O3

# Build options.
CFLAGS	:= -Wall $(OPT) -ggdb
CPPFLAGS := -I$(BUILD)/include
LIBS	:= -lm

# Comment/uncomment for debugging.
CPPFLAGS += #-D_DEBUG
