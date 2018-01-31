# General build flags

CXXFLAGS = -O3 -g -Wall -fmessage-length=0
ARFLAGS = -rv

# Main executable

OBJS =	planets-c++.o

PLANETS_LIB_OBJS =	CelestialBody.o CSVBodyParser.o Planet.o DwarfPlanet.o

libplanets.a: $(PLANETS_LIB_OBJS)
	ar $(ARFLAGS) $@ $^

LIBS = libplanets.a

TARGET =	planets-c++

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all: $(LIBS) $(TARGET)

# Tests

TEST_TARGETS= CelestialBodyTest CSVBodyParserTest PlanetTest DwarfPlanetTest

test: $(LIBS) $(TEST_TARGETS) $(addprefix run-,$(TEST_TARGETS))

BOOST_TEST_LIBS =	 boost_unit_test_framework

%: tests/%.cpp
	$(CXX) -o $@ $^ -l$(BOOST_TEST_LIBS) $(LIBS)

run-%: %
	-./$^ --log_level=test_suite

# Clean up

clean:
	rm -f $(OBJS) $(TARGET) libplanets.a $(PLANETS_LIB_OBJS) $(TESTS_LIB_OBJS) libplanetsTests.a $(TEST_TARGETS) tests/*.o
