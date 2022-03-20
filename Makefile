ROOT_PATH ?= $(CURDIR)

APP_PATH = $(ROOT_PATH)/application
BUILD_PATH = $(ROOT_PATH)/build
LIB_PATH = $(ROOT_PATH)/lib
PLATFORM_PATH = $(ROOT_PATH)/platform
THIRDPART_PATH = $(ROOT_PATH)/thirdpart
TOOL_PATH = $(ROOT_PATH)/tool
BUILD_CONFIG_PATH = $(BUILD_PATH)/kbuild
TARGET_PATH = $(ROOT_PATH)/build/out

include $(TOOL_PATH)/make/makePath
include $(TOOL_PATH)/make/makeConfig

#获取所有头文件路径
INCLUDE_PATH = $(addsuffix /include, $(subdirs-y))

export C_FLAGS += $(addprefix -I$(ROOT_PATH)/, $(INCLUDE_PATH))

#生成目标
LIB_STATIC = $(wildcard $(TARGET_PATH)/*.a)
TARGET ?= $(BUILD_PATH)/outbin

.PHONY: all clean dist-clean

all: $(TARGET)

$(TARGET): subsrc
	$(shell test -d $(BUILD_PATH)|| mkdir -p $(BUILD_PATH))
	$(Q)echo -e "\033[33m CREATE $(notdir $@)\033[0m"
	$(Q)$(CC) $(C_FLAGS) $(LD_FLAGS) $(LIB_STATIC) -o $@

subsrc:
	$(Q)for subdir in $(subdirs-y); do \
		$(MAKE) -C $(ROOT_PATH)/$$subdir -j ROOT_PATH=$(ROOT_PATH) TOOL_PATH=$(TOOL_PATH) BUILD_PATH=$(BUILD_PATH) TARGET_PATH=$(TARGET_PATH); \
		if [ $$? != 0 ]; then echo "make $$subdir fail"; exit 1; fi; \
	done


menuconfig : $(BUILD_CONFIG_PATH)/kconfig/mconf
	$(Q)$< $(ROOT_PATH)/Kconfig

$(BUILD_CONFIG_PATH)/kconfig/mconf: 
	$(Q)mkdir -p $(BUILD_CONFIG_PATH)
	$(Q)make -C $(TOOL_PATH)/kbuild -f ./Makefile.sample O=$(BUILD_CONFIG_PATH) -j

clean:
	$(Q)rm -r $(BUILD_PATH)/*
	$(Q)rm -r $(BUILD_PATH)

dist-clean:
	$(Q)rm -r $(BUILD_PATH)/* .config .config.old
	$(Q)rm -r $(BUILD_PATH)
