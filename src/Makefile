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
# Build the myrt code.
#

# Specify our sources.
OBJECTS	:= 

# Programs to build.
PROGS	:= 

# Get access to build commands, include path, etc.
include $(BUILD)/config.mk

# Normal build targets, etc, etc.
all: $(PROGS)

# Some special targets to make the build commands look pretty.
$(PROGS): %: %.c $(OBJECTS) 
	$(MSG) " [CCLD] " $@
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $@.c $(OBJECTS) $(LIBS)

# The lexxer source compiliation.
#lexxer.c: lexxer.l
#	$(MSG) " [LEX]  " $@
#	$(LEX) -o $@ lexxer.l

# Pull in dynamically generated dependencies. For some reason this has to
# be *below* the $(PROGS) target. Whatever...
-include .*.d
.c.o:
	$(MSG) " [CC]   " $@
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	$(CC) -MM $(CFLAGS) $(CPPFLAGS) -c $< > .$(@:.o=.d)

clean:
	$(MSG) " [CLEAN]" $(OBJECTS) $(PROGS) lexxer.c
	@rm -f $(OBJECTS) $(PROGS) lexxer.c
	@rm -f .*.d
