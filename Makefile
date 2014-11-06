# If the tool is built out of the kit, PIN_ROOT must be specified in the make invocation and point to the kit root.
ifdef PIN_ROOT
CONFIG_ROOT := $(PIN_ROOT)/source/tools/Config
else
$(error Please specify pin root directory)
endif

include $(CONFIG_ROOT)/makefile.config
include makefile.rules
include $(TOOLS_ROOT)/Config/makefile.default.rules

benchmarks: simple

simple:
	$(MAKE) -C ./Tests/simple/ all

benchmarks_clean: simple_clean

simple_clean:
	$(MAKE) -C ./Tests/simple/ clean
