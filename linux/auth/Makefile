KERNEL_DIR :=$(srctree)

EXTRA_CFLAGS += -I$(KERNEL_DIR)/drivers/tzdriver
EXTRA_CFLAGS += -I$(KERNEL_DIR)/drivers/tzdriver/core
EXTRA_CFLAGS += -I$(KERNEL_DIR)/drivers/tzdriver/tlogger
EXTRA_CFLAGS += -I$(KERNEL_DIR)/../../../../third_party/bounds_checking_function/include
EXTRA_CFLAGS += -I$(KERNEL_DIR)/drivers/tzdriver/include
EXTRA_CFLAGS += -I$(KERNEL_DIR)/../../../../base/security/selinux/include
EXTRA_CFLAGS += -I$(KERNEL_DIR)/../../../../base/security/selinux

EXTRA_CFLAGS += -DSELINUX_CA_HIDL_LABEL=\"u:r:hal_libteec_default:s0\"
EXTRA_CFLAGS += -DSELINUX_TEECD_LABEL=\"u:r:tee:s0\"
ifneq ($(CONFIG_TZDRIVER_OHOS),y)
EXTRA_CFLAGS += -DCONFIG_SELINUX_AUTH_ENABLE
endif
ifeq ($(CONFIG_CADAEMON_AUTH),y)
EXTRA_CFLAGS += -DCADAEMON_PATH_UID_AUTH_CTX=\"/system/bin/sa_main:6668\"
EXTRA_CFLAGS += -DSELINUX_CADAEMON_LABEL=NULL
endif
ifeq ($(CONFIG_TZDRIVER_OHOS),y)
EXTRA_CFLAGS += -DTEECD_PATH_UID_AUTH_CTX=\"/vendor/bin/teecd:6668\"
else
EXTRA_CFLAGS += -DTEECD_PATH_UID_AUTH_CTX=\"/vendor/bin/teecd:0\"
endif

obj-$(CONFIG_CLIENT_AUTH) += client_hash_auth.o

ifeq ($(findstring y, $(CONFIG_TEECD_AUTH) $(CONFIG_CLIENT_AUTH)), y)
	obj-y += auth_base_impl.o
endif
