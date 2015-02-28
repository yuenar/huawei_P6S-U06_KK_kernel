PRODUCT_NAME := EDGE_PLUS_UL_VY
PRODUCT_BRAND := Huawei
#add macro to enable command type lcd
export USE_LCD_JDI_OTM1282B := true

#NOTICE! Do not config PRODUCT_DEVICE
export USE_EDGE_CAMERA_SETTINGS := true
export USE_AUDIO_RING_VOLUME_CHANGE := true
PRODUCT_LCD_DISPLAY=HD
DOLBY_AUDIOEFFECT_DM:=true
ifeq ($(TARGET_VERSION_MODE),normal)
PRODUCT_PACKAGES += check_root
endif
$(call inherit-product, frameworks/native/build/phone-xhdpi-2048-dalvik-heap.mk)

