# Standard things
sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)
BUILDDIRS += $(BUILD_PATH)/$(d)
BUILDDIRS += $(BUILD_PATH)/$(d)/ulib

CORE_INCLUDES := -I$(INCLUDE_PATH) -I$(CORE_PATH) -I$(PLATFORM_PATH)

# Local flags /* here need more INCLUDES if more sub dirs */
CFLAGS_$(d) := -I$(d) -I$(PLATFORM_PATH)/$(TARGET_PLATFORM) -I$(d)/ulib $(CORE_INCLUDES) -Wall -Werror

# Local rules and targets (add source files here)
cSRCS_$(d) := \
	sys_main.c \
	sys_print.c \
	sys_mm.c \
	mm_std.c \
	sys_time.c \
	sys_sched.c \
	sys_sync.c \
	sys_utils.c \
	sys_ictl.c \
	sys_debug.c \
	sys_ds.c

# ulib
cSRCS_$(d) += ulib/string.c ulib/stdlib.c

sSRCS_$(d) :=

cFILES_$(d) := $(cSRCS_$(d):%=$(d)/%)
sFILES_$(d) := $(sSRCS_$(d):%=$(d)/%)

OBJS_$(d) := $(cFILES_$(d):%.c=$(BUILD_PATH)/%.o)
DEPS_$(d) := $(OBJS_$(d):%.o=%.d)

$(OBJS_$(d)): TGT_CFLAGS := $(CFLAGS_$(d))
$(OBJS_$(d)): TGT_ASFLAGS :=

TGT_BIN += $(OBJS_$(d))

# Standard things
-include $(DEPS_$(d))
d := $(dirstack_$(sp))
sp := $(basename $(sp))
