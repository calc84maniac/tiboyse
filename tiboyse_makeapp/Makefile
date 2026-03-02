# --- Compiler flags -------------------------------------------------------

CFLAGS   := -Oz -Wall -Irabbitsign/src
CXXFLAGS := $(CFLAGS) --std=c++17
LDFLAGS  :=
LDLIBS   := -lgmp

# --- Paths --------------------------------------------------------------------

RABBIT_DIR := rabbitsign
RABBIT_SRC := $(RABBIT_DIR)/src
RABBIT_LIB := $(RABBIT_SRC)/librabbitsign.a

# --- Targets ------------------------------------------------------------------

all: tiboyse_makeapp

# Build the real rabbitsign submodule (64-bit)
$(RABBIT_LIB):
	cd $(RABBIT_DIR) && ./configure
	$(MAKE) -C $(RABBIT_SRC)

# Build makeapp
makeapp.o: makeapp.cpp
	$(CXX) $(CXXFLAGS) -c makeapp.cpp -o makeapp.o

tiboyse_makeapp: makeapp.o $(RABBIT_LIB)
	$(CXX) $(LDFLAGS) -o $@ makeapp.o $(RABBIT_LIB) $(LDLIBS)

# --- Clean --------------------------------------------------------------------

clean:
	rm -f makeapp.o tiboyse_makeapp
	$(MAKE) -C $(RABBIT_DIR) distclean || true

.PHONY: all clean

