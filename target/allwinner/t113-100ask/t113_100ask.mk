$(call inherit-product-if-exists, target/allwinner/t113-common/t113-common.mk)

PRODUCT_PACKAGES +=

PRODUCT_COPY_FILES +=

PRODUCT_AAPT_CONFIG := large xlarge hdpi xhdpi
PRODUCT_AAPT_PERF_CONFIG := xhdpi
PRODUCT_CHARACTERISTICS := musicbox

PRODUCT_BRAND := allwinner
PRODUCT_NAME := t113_100ask
PRODUCT_DEVICE := t113-100ask
PRODUCT_MODEL := Allwinner t113 100ask pro board
