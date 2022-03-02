CC = g++
CXXFLAGS := -g -Og
CXXFLAGS += -I../include
CXXFLAGS += -fpermissive

TARGETS := \
	test-vector \
	test-fixed-vector

all: clean $(TARGETS)

%: %.cpp
	$(CC) $(CXXFLAGS) $< -o $@ $(LIBS)

run: all
	@for ITEM in $(TARGETS); do \
		$(shell pwd)/$$ITEM; \
		[ $$? -eq 0 ] && { echo "[PASS] - $$ITEM"; } \
		              || { echo ">> [FAIL] - $$ITEM"; }; \
	done

clean:
	@rm -rf $(TARGETS)
