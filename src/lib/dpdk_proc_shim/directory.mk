#
# Makefile stub for dpdk process shim library
#

DPS_SOURCES += \
	api.cpp \
	primary.cpp \
	secondary.cpp

$(DPS_OBJ_DIR)/%.o: OP_CPPFLAGS += -Wno-register -Wno-deprecated-declarations
