#
# Makefile component for the DPDK process shim library
#

DPS_REQ_VARS := \
	OP_ROOT \
	OP_BUILD_ROOT
$(call op_check_vars,$(DPS_REQ_VARS))

DPS_SRC_DIR := $(OP_ROOT)/src/lib/dpdk_proc_shim
DPS_INC_DIR := $(dir $(DPS_SRC_DIR))
DPS_OBJ_DIR := $(OP_BUILD_ROOT)/obj/lib/dpdk_proc_shim
DPS_LIB_DIR := $(OP_BUILD_ROOT)/lib

DPS_DEPENDS := dpdk
DPS_SOURCES :=

include $(DPS_SRC_DIR)/directory.mk

DPS_OBJECTS := $(call op_generate_objects,$(DPS_SOURCES),$(DPS_OBJ_DIR))


DPS_LIBRARY := dpdk_process_shim
DPS_TARGET := $(DPS_LIB_DIR)/lib$(DPS_LIBRARY).a

# Load external dependencies
-include $(DPS_OBJECTS:.o=.d)
$(call op_include_dependencies,$(DPS_DEPENDS))

OP_INC_DIRS += $(DPS_INC_DIR)
OP_LIB_DIRS += $(DPS_LIB_DIR)
OP_LDLIBS += -l$(DPS_LIBRARY)

###
# Build rules
###
$(eval $(call op_generate_build_rules,$(DPS_SOURCES),DPS_SRC_DIR,DPS_OBJ_DIR,DPS_DEPENDS))
$(eval $(call op_generate_clean_rules,dpdk_proc_shim,DPS_TARGET,DPS_OBJECTS))

$(DPS_TARGET): $(DPS_OBJECTS)
	$(call op_link_library,$@,$(DPS_OBJECTS))

.PHONY: dpdk_proc_shim
dpdk_proc_shim: $(DPS_TARGET)
