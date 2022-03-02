CC = g++
CXXFLAGS := -I../include
CXXFLAGS += -fpermissive

TARGETS := \
	test-fixed-vector

all: clean $(TARGETS)

%: %.cpp
	$(CC) $(CXXFLAGS) $< -o $@ $(LIBS)
	$(shell pwd)/$@

clean:
	@rm -rf $(TARGETS)
