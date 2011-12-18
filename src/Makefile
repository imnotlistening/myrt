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
OBJECTS	:= lexxer.o parser.o builtin_shapes.o core.o settings.o \
		screen.o obj_list.o color.o light.o command.o shade.o \
		post_process.o

# Lexxers.
LEXXERS := lexxer.c

# Programs to build.
PROGS		:= myrt $(subst .c,,$(shell ls tests/*.c))
PROJ_LIBS	:= libmyrt.so
PROJ_LIB_FLAGS	:= -L. $(subst lib,-l, $(subst .so,, $(PROJ_LIBS)))

# Get access to build commands, include path, etc.
include $(BUILD)/config.mk

# Determine whether we should build architecure specific assembly of whether
# we should just build the generic C code for the vector arithmetic.
ifeq ($(ARCH), )
OBJECTS += arch/vec_generic.o
else
OBJECTS += argc/vec_$(ARCH).o
endif

# Build a list of dependency files.
DEPS	:= $(shell find | grep \\.d$)

# Normal build targets, etc, etc.
all: $(PROJ_LIBS) $(PROGS)

# Some special targets to make the build commands look pretty.
$(PROGS): %: %.c 
	$(MSG) " [CCLD] " $@
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $@.c $(LIBS) $(PROJ_LIB_FLAGS)

# Library building targets.
libmyrt.so: $(OBJECTS)
	$(MSG) " [LD]   " $@
	$(LD) -shared -Wl,-soname=$@ $(OBJECTS) -o $@.$(VERSION) $(LIBS)
	@ldconfig -n .

# Lexxer source compiliation, if necessary.
.l.c:
	$(MSG) " [LEX]  " $@
	$(LEX) -o $@ $<

# Pull in dynamically generated dependencies. For some reason this has to
# be *below* the $(PROGS) target. Whatever...
-include $(DEPS)
.c.o: $(LEXXERS)
	$(MSG) " [CC]   " $@
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	$(CC) -MM $(CFLAGS) $(CPPFLAGS) -c $< > \
		$(dir $(@)).$(notdir $(@:.o=.d))

clean:
	$(MSG) " [CLEAN]" $(PROGS) $(PROJ_LIBS)* $(OBJECTS) $(LEXXERS)
	@rm -f $(OBJECTS) $(PROGS) $(PROJ_LIBS)* $(LEXXERS)
	@rm -f $(DEPS)
