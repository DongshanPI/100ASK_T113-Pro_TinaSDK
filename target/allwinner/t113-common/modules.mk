#
# Copyright (C) 2015-2016 Allwinner
#
# This is free software, licensed under the GNU General Public License v2.
# See /build/LICENSE for more information.
#
define KernelPackage/sunxi-vin
  SUBMENU:=$(VIDEO_MENU)
  TITLE:=sunxi-vin support
  FILES:=$(LINUX_DIR)/drivers/media/common/videobuf2/videobuf2-memops.ko
  FILES+=$(LINUX_DIR)/drivers/media/common/videobuf2/videobuf2-dma-contig.ko
  FILES+=$(LINUX_DIR)/drivers/media/platform/sunxi-vin/vin_io.ko
  FILES+=$(LINUX_DIR)/drivers/media/platform/sunxi-vin/modules/sensor/ov5640.ko
  FILES+=$(LINUX_DIR)/drivers/media/platform/sunxi-vin/vin_v4l2.ko
  KCONFIG:=\
	CONFIG_MEDIA_SUPPORT=y \
	CONFIG_MEDIA_CAMERA_SUPPORT=y \
    CONFIG_V4L_PLATFORM_DRIVERS=y \
    CONFIG_MEDIA_CONTROLLER=y \
    CONFIG_MEDIA_SUBDRV_AUTOSELECT=y \
	CONFIG_SUNXI_PLATFORM_DRIVERS=y \
    CONFIG_VIDEO_SUNXI_VIN \
    CONFIG_CSI_VIN \
	CONFIG_CSI_CCI=n \
	CONFIG_I2C_SUNXI=y
  AUTOLOAD:=$(call AutoLoad,90,videobuf2-memops videobuf2-dma-contig vin_io ov5640 vin_v4l2)
endef

define KernelPackage/sunxi-vin/description
  Kernel modules for sunxi-vin support
endef

$(eval $(call KernelPackage,sunxi-vin))

define KernelPackage/sunxi-uvc
  SUBMENU:=$(VIDEO_MENU)
  TITLE:=sunxi-uvc support
  FILES:=$(LINUX_DIR)/drivers/media/common/videobuf2/videobuf2-common.ko
  FILES+=$(LINUX_DIR)/drivers/media/common/videobuf2/videobuf2-v4l2.ko
  FILES+=$(LINUX_DIR)/drivers/media/common/videobuf2/videobuf2-memops.ko
  FILES+=$(LINUX_DIR)/drivers/media/common/videobuf2/videobuf2-vmalloc.ko
  FILES+=$(LINUX_DIR)/drivers/media/usb/uvc/uvcvideo.ko
  KCONFIG:= \
	CONFIG_MEDIA_SUPPORT=y \
	CONFIG_MEDIA_CAMERA_SUPPORT=y \
    CONFIG_V4L_PLATFORM_DRIVERS=y \
    CONFIG_MEDIA_CONTROLLER=y \
    CONFIG_MEDIA_SUBDRV_AUTOSELECT=y \
    CONFIG_MEDIA_USB_SUPPORT=y \
	CONFIG_VIDEO_V4L2=y \
    CONFIG_USB_VIDEO_CLASS \
    CONFIG_USB_VIDEO_CLASS_INPUT_EVDEV
  AUTOLOAD:=$(call AutoLoad,95,videobuf2-common videobuf2-v4l2 videobuf2-memops videobuf2_vmalloc uvcvideo)
endef

define KernelPackage/sunxi-uvc/description
  Kernel modules for sunxi-uvc support
endef

$(eval $(call KernelPackage,sunxi-uvc))

define KernelPackage/net-broadcom
  SUBMENU:=$(WIRELESS_MENU)
  DEPENDS:= +ap6256-firmware +@PACKAGE_broadcom-rftest
  TITLE:=broadcom(ap6256...) support
  FILES:=$(LINUX_DIR)/drivers/net/wireless/bcmdhd/bcmdhd.ko
  KCONFIG:=\
	  CONFIG_BCMDHD=m \
	  CONFIG_BCMDHD_SDIO=y \
	  CONFIG_BCMDHD_OOB=y \
	  CONFIG_BCMDHD_FW_PATH="/etc/firmware/fw_bcmdhd.bin" \
	  CONFIG_BCMDHD_NVRAM_PATH="/etc/firmware/nvram.txt" \
	  CONFIG_BCMDHD_SDIO=y \
	  CONFIG_SUNXI_RFKILL=y \
	  CONFIG_MMC=y \
	  CONFIG_PWRSEQ_EMMC=y \
	  CONFIG_PWRSEQ_SIMPLE=y \
	  CONFIG_MMC_SUNXI=y \
	  CONFIG_MMC_SUNXI_V4P1X=y \
	  CONFIG_MMC_SUNXI_V4P00X=y \
	  CONFIG_MMC_SUNXI_V4P10X=y \
	  CONFIG_MMC_SUNXI_V4P5X=y \
	  CONFIG_MMC_SUNXI_V5P3X=y \

  AUTOLOAD:=$(call AutoProbe,bcmdhd,1)
endef

define KernelPackage/net-broadcom/description
 Kernel modules for Broadcom AP6256...  support
endef

$(eval $(call KernelPackage,net-broadcom))

define KernelPackage/net-xr829-40M
  SUBMENU:=$(WIRELESS_MENU)
  TITLE:=xr829 support (staging)
  DEPENDS:= +xr829-firmware +@IPV6 +@XR829_USE_40M_SDD +@USES_XR829 +@PACKAGE_xr829-rftest
  KCONFIG:=\
	CONFIG_XR829_WLAN=m \
	CONFIG_PM=y\
	CONFIG_BT=y \
	CONFIG_BT_BREDR=y \
	CONFIG_BT_RFCOMM=y \
	CONFIG_BT_RFCOMM_TTY=y \
	CONFIG_BT_DEBUGFS=y \
	CONFIG_XR_BT_LPM=y \
	CONFIG_XR_BT_FDI=y \
	CONFIG_BT_HCIUART=y \
	CONFIG_BT_HCIUART_H4=y \
	CONFIG_HFP_OVER_PCM=y \
	CONFIG_RFKILL=y \
	CONFIG_RFKILL_PM=y \
	CONFIG_RFKILL_GPIO=y

  #FILES:=$(LINUX_DIR)/drivers/net/wireless/xr829/wlan/xradio_core.ko
  #FILES+=$(LINUX_DIR)/drivers/net/wireless/xr829/wlan/xradio_wlan.ko
  #FILES+=$(LINUX_DIR)/drivers/net/wireless/xr829/umac/xradio_mac.ko
  #AUTOLOAD:=$(call AutoProbe, xradio_mac xradio_core xradio_wlan)

  FILES:=$(LINUX_DIR)/drivers/net/wireless/xr829/xr829.ko
ifeq ($(CONFIG_PACKAGE_kmod-sunxi-sdmmc), y)  
  FILES+=$(LINUX_DIR)/drivers/mmc/host/sunxi_mmc_host.ko
endif  
  AUTOLOAD:=$(call AutoProbe, xr829)
endef

define KernelPackage/net-xr829-40M/description
 Kernel modules for xr829 support
endef

$(eval $(call KernelPackage,net-xr829-40M))


define KernelPackage/net-xr829
  SUBMENU:=$(WIRELESS_MENU)
  TITLE:=xr829 support (staging)
  DEPENDS:= +xr829-firmware +@IPV6 +@USES_XR829 +@PACKAGE_xr829-rftest +@PACKAGE_xr829-rftest
  KCONFIG:=\
	CONFIG_XR829_WLAN=m \
	CONFIG_PM=y\
	CONFIG_BT=y \
	CONFIG_BT_BREDR=y \
	CONFIG_BT_RFCOMM=y \
	CONFIG_BT_RFCOMM_TTY=y \
	CONFIG_BT_DEBUGFS=y \
	CONFIG_XR_BT_LPM=y \
	CONFIG_XR_BT_FDI=y \
	CONFIG_BT_HCIUART=y \
	CONFIG_BT_HCIUART_H4=y \
	CONFIG_HFP_OVER_PCM=y \
	CONFIG_RFKILL=y \
	CONFIG_RFKILL_PM=y \
	CONFIG_RFKILL_GPIO=y


  #FILES:=$(LINUX_DIR)/drivers/net/wireless/xr829/wlan/xradio_core.ko
  #FILES+=$(LINUX_DIR)/drivers/net/wireless/xr829/wlan/xradio_wlan.ko
  #FILES+=$(LINUX_DIR)/drivers/net/wireless/xr829/umac/xradio_mac.ko
  #AUTOLOAD:=$(call AutoProbe, xradio_mac xradio_core xradio_wlan)

  FILES+=$(LINUX_DIR)/drivers/net/wireless/xr829/xr829.ko
ifeq ($(CONFIG_PACKAGE_kmod-sunxi-sdmmc), y)  
  FILES+=$(LINUX_DIR)/drivers/mmc/host/sunxi_mmc_host.ko
endif  
  AUTOLOAD:=$(call AutoProbe, xr829)
endef

define KernelPackage/net-xr829/description
 Kernel modules for xr829 support
endef

$(eval $(call KernelPackage,net-xr829))

define KernelPackage/net-xr819s-40M
  SUBMENU:=$(WIRELESS_MENU)
  TITLE:=xr819s support (staging)
  DEPENDS:= +xr819s-firmware +@IPV6 +@XR819S_USE_40M_SDD +@USES_XR819S +@PACKAGE_xr819S-rftest
  KCONFIG:=\
	CONFIG_XR819S_WLAN=m \
	CONFIG_PM=y\
	CONFIG_BT=n \
	CONFIG_BT_BREDR=n \
	CONFIG_BT_RFCOMM=n \
	CONFIG_BT_RFCOMM_TTY=n \
	CONFIG_BT_DEBUGFS=n \
	CONFIG_XR_BT_LPM=n \
	CONFIG_XR_BT_FDI=n \
	CONFIG_BT_HCIUART=n \
	CONFIG_BT_HCIUART_H4=n \
	CONFIG_HFP_OVER_PCM=n \
	CONFIG_RFKILL=n \
	CONFIG_RFKILL_PM=n \
	CONFIG_RFKILL_GPIO=n

  #FILES:=$(LINUX_DIR)/drivers/net/wireless/xr819s/wlan/xradio_core.ko
  #FILES+=$(LINUX_DIR)/drivers/net/wireless/xr819s/wlan/xradio_wlan.ko
  #FILES+=$(LINUX_DIR)/drivers/net/wireless/xr819s/umac/xradio_mac.ko
  #AUTOLOAD:=$(call AutoProbe, xradio_mac xradio_core xradio_wlan)

  FILES:=$(LINUX_DIR)/drivers/net/wireless/xr819s/xr819s.ko
ifeq ($(CONFIG_PACKAGE_kmod-sunxi-sdmmc), y)  
  FILES+=$(LINUX_DIR)/drivers/mmc/host/sunxi_mmc_host.ko
endif
  AUTOLOAD:=$(call AutoProbe, xr819s)
endef

define KernelPackage/net-xr819s-40M/description
 Kernel modules for xr819s support
endef

$(eval $(call KernelPackage,net-xr819s-40M))

define KernelPackage/sunxi-sdmmc
  SUBMENU:=$(OTHER_MENU)
  TITLE:=sunxi-sdmmc support
  KCONFIG:= \
	CONFIG_MMC=y \
	CONFIG_MMC_BLOCK=m \
	CONFIG_MMC_SUNXI=m \
	CONFIG_MMC_SUNXI_V4P1X=y \
	CONFIG_MMC_SUNXI_V4P00X=y \
	CONFIG_MMC_SUNXI_V4P10X=y	\
	CONFIG_MMC_SUNXI_V4P5X=y	\
	CONFIG_MMC_SUNXI_V5P3X=y	
  FILES+=$(LINUX_DIR)/drivers/mmc/core/mmc_block.ko
  FILES+=$(LINUX_DIR)/drivers/mmc/host/sunxi_mmc_host.ko
  AUTOLOAD:=$(call AutoProbe,sunxi-sdmmc)
endef

define KernelPackage/sunxi-sdmmc/description
  Kernel modules for sun20iw1-sdmmc support
endef
$(eval $(call KernelPackage,sunxi-sdmmc))

define KernelPackage/net-xr819s
  SUBMENU:=$(WIRELESS_MENU)
  TITLE:=xr819s support (staging)
  #DEPENDS:= +xr819s-firmware +@IPV6 +@USES_XR819S +@PACKAGE_xr819s-rftest +@PACKAGE_xr819s-rftest
  DEPENDS:= +xr819s-firmware +@IPV6 +@USES_XR819S +@PACKAGE_xr819s-rftest +@USES_XRADIO
  KCONFIG:=\
	CONFIG_XR819S_WLAN=m \
	CONFIG_PM=y\
	CONFIG_BT=n \
	CONFIG_BT_BREDR=n \
	CONFIG_BT_RFCOMM=n \
	CONFIG_BT_RFCOMM_TTY=n \
	CONFIG_BT_DEBUGFS=n \
	CONFIG_XR_BT_LPM=n \
	CONFIG_XR_BT_FDI=n \
	CONFIG_BT_HCIUART=n \
	CONFIG_BT_HCIUART_H4=n \
	CONFIG_HFP_OVER_PCM=n \
	CONFIG_SUNXI_RFKILL=m\
	CONFIG_SUNXI_ADDR_MGT=m\
	CONFIG_RFKILL=n \
	CONFIG_RFKILL_PM=n \
	CONFIG_RFKILL_GPIO=n

  #FILES:=$(LINUX_DIR)/drivers/net/wireless/xr819s/wlan/xradio_core.ko
  #FILES+=$(LINUX_DIR)/drivers/net/wireless/xr819s/wlan/xradio_wlan.ko
  #FILES+=$(LINUX_DIR)/drivers/net/wireless/xr819s/umac/xradio_mac.ko
  #AUTOLOAD:=$(call AutoProbe, xradio_mac xradio_core xradio_wlan)

  FILES:=$(LINUX_DIR)/drivers/net/wireless/xr819s/xr819s.ko
  FILES+=$(LINUX_DIR)/drivers/misc/sunxi-addr/sunxi_addr.ko
  FILES+=$(LINUX_DIR)/drivers/misc/sunxi-rf/sunxi_rfkill.ko
ifeq ($(CONFIG_PACKAGE_kmod-sunxi-sdmmc), y)  
  FILES+=$(LINUX_DIR)/drivers/mmc/host/sunxi_mmc_host.ko
endif
  AUTOLOAD:=$(call AutoProbe, xr819s)
endef

define KernelPackage/net-xr819s/description
 Kernel modules for xr819s support
endef

$(eval $(call KernelPackage,net-xr819s))

define KernelPackage/net-rtl8821cs
  SUBMENU:=$(WIRELESS_MENU)
  TITLE:=RTL8821CS support (staging)
  DEPENDS:= +rtl8821cs-firmware +@IPV6
  FILES:=$(LINUX_DIR)/drivers/net/wireless/rtl8821cs/8821cs.ko
  AUTOLOAD:=$(call AutoProbe,8821cs)
endef

define KernelPackage/net-rtl8821cs/description
 Kernel modules for RealTek RTL8821CS support
endef

$(eval $(call KernelPackage,net-rtl8821cs))

define KernelPackage/sunxi-disp
  SUBMENU:=$(VIDEO_MENU)
  TITLE:=sunxi-disp support
  KCONFIG:=\
	  CONFIG_DISP2_SUNXI=m \
	  #CONFIG_SUNXI_DISP2_FB_DISABLE_ROTATE=y \
	  #CONFIG_SUNXI_DISP2_FB_ROTATION_SUPPORT=n \
	  #CONFIG_SUNXI_DISP2_FB_HW_ROTATION_SUPPORT=n \
	  CONFIG_DISP2_SUNXI_BOOT_COLORBAR=n \
	  CONFIG_DISP2_SUNXI_DEBUG=y \
	  CONFIG_DISP2_SUNXI_COMPOSER=n \
	  CONFIG_DISP2_SUNXI_SUPPORT_SMBL=y \
	  CONFIG_DISP2_SUNXI_SUPPORT_ENAHNCE=y \
	  CONFIG_SUNXI_DISP2_FB_DECOMPRESS_LZMA=n \
	  CONFIG_VDPO_DISP2_SUNXI=n \
	  CONFIG_EDP_DISP2_SUNXI=n \
	  CONFIG_HDMI_DISP2_SUNXI=n \
	  CONFIG_HDMI2_DISP2_SUNXI=n \
	  CONFIG_HDMI_EP952_DISP2_SUNXI=n \
	  CONFIG_TV_DISP2_SUNXI=n \
	  CONFIG_DISP2_LCD_ESD_DETECT=n \
	  CONFIG_LCD_FB=n \
	  CONFIG_LCD_FB_ENABLE_DEFERRED_IO=n \
	  CONFIG_FB=y \
	  CONFIG_FB_CMDLINE=y \
	  CONFIG_FB_CONSOLE_SUNXI=n \
	  CONFIG_FRAMEBUFFER_CONSOLE=n \
	  CONFIG_FRAMEBUFFER_CONSOLE_DETECT_PRIMARY=n \
	  CONFIG_FRAMEBUFFER_CONSOLE_ROTATION=n \
	  CONFIG_LCD_SUPPORT_GG1P4062UTSW=n \
	  CONFIG_LCD_SUPPORT_DX0960BE40A1=n \
	  CONFIG_LCD_SUPPORT_TFT720X1280=n \
	  CONFIG_LCD_SUPPORT_FD055HD003S=n \
	  CONFIG_LCD_SUPPORT_HE0801A068=n \
	  CONFIG_LCD_SUPPORT_ILI9341=n \
	  CONFIG_LCD_SUPPORT_LH219WQ1=n \
	  CONFIG_LCD_SUPPORT_LS029B3SX02=n \
	  CONFIG_LCD_SUPPORT_LT070ME05000=n \
	  CONFIG_LCD_SUPPORT_S6D7AA0X01=n \
	  CONFIG_LCD_SUPPORT_T27P06=n \
	  CONFIG_LCD_SUPPORT_TFT720x1280=n \
	  CONFIG_LCD_SUPPORT_WTQ05027D01=n \
	  CONFIG_LCD_SUPPORT_H245QBN02=n \
	  CONFIG_LCD_SUPPORT_ST7789V=n \
	  CONFIG_LCD_SUPPORT_ST7796S=n \
	  CONFIG_LCD_SUPPORT_ST7701S=n \
	  CONFIG_LCD_SUPPORT_T30P106=n \
	  CONFIG_LCD_SUPPORT_TO20T20000=n \
	  CONFIG_LCD_SUPPORT_FRD450H40014=n \
	  CONFIG_LCD_SUPPORT_S2003T46G=n \
	  CONFIG_LCD_SUPPORT_WILLIAMLCD=n \
	  CONFIG_LCD_SUPPORT_LQ101R1SX03=n \
	  CONFIG_LCD_SUPPORT_INET_DSI_PANEL=n \
	  CONFIG_LCD_SUPPORT_WTL096601G03=n \
	  CONFIG_LCD_SUPPORT_RT13QV005D=n \
	  CONFIG_LCD_SUPPORT_ST7789V_CPU=n \
	  CONFIG_LCD_SUPPORT_CC08021801_310_800X1280=n \
	  CONFIG_DRM=n
  FILES+=$(LINUX_DIR)/drivers/video/fbdev/sunxi/disp2/disp/disp.ko
  AUTOLOAD:=$(call AutoLoad,10,disp,1)
endef

define KernelPackage/sunxi-disp/description
  Kernel modules for sunxi-disp support
endef

$(eval $(call KernelPackage,sunxi-disp))

define KernelPackage/sunxi-hdmi
  SUBMENU:=$(VIDEO_MENU)
  TITLE:=sunxi-hdmi support
  DEPENDS:=+kmod-sunxi-disp
  KCONFIG:=\
	  CONFIG_HDMI2_DISP2_SUNXI=m \
	  CONFIG_AW_PHY=y \
	  CONFIG_DEFAULT_PHY=n \
	  CONFIG_HDMI2_HDCP_SUNXI=y \
	  CONFIG_HDMI2_HDCP22_SUNXI=n \
	  CONFIG_HDMI2_CEC_SUNXI=y \
	  CONFIG_HDMI2_CEC_USER=n \
	  CONFIG_HDMI2_FREQ_SPREAD_SPECTRUM=n
  FILES+=$(LINUX_DIR)/drivers/video/fbdev/sunxi/disp2/hdmi2/hdmi20.ko
  AUTOLOAD:=$(call AutoLoad,15,hdmi20,1)
endef

define KernelPackage/sunxi-hdmi/description
  Kernel modules for sunxi-hdmi support
endef

$(eval $(call KernelPackage,sunxi-hdmi))

define KernelPackage/sunxi-g2d
  SUBMENU:=$(VIDEO_MENU)
  TITLE:=sunxi-g2d support
  KCONFIG:=\
	  CONFIG_SUNXI_G2D=y \
	  CONFIG_SUNXI_G2D_MIXER=y \
	  CONFIG_SUNXI_G2D_ROTATE=y \
	  CONFIG_SUNXI_SYNCFENCE=n
  FILES+=$(LINUX_DIR)/drivers/char/sunxi_g2d/g2d_sunxi.ko
  AUTOLOAD:=$(call AutoLoad,20,g2d_sunxi,1)
endef

define KernelPackage/sunxi-g2d/description
  Kernel modules for sunxi-g2d support
endef

$(eval $(call KernelPackage,sunxi-g2d))

define KernelPackage/touchscreen-gt9xxnew
  SUBMENU:=$(INPUT_MODULES_MENU)
  TITLE:=gt9xxnew support
  DEPENDS:= +kmod-input-core
  KCONFIG:= \
	CONFIG_INPUT_TOUCHSCREEN=y \
	CONFIG_I2C_SUNXI=m \
	CONFIG_INPUT_SENSORINIT=m \
	CONFIG_TOUCHSCREEN_SUNXI=m \
	CONFIG_TOUCHSCREEN_BU21029=n \
	CONFIG_TOUCHSCREEN_EGALAX_SERIAL=n \
	CONFIG_TOUCHSCREEN_EXC3000=n \
	CONFIG_TOUCHSCREEN_HIDEEP=n \
	CONFIG_TOUCHSCREEN_S6SY761=n \
	CONFIG_TOUCHSCREEN_EKTF2127=n \
	CONFIG_TOUCHSCREEN_MELFAS_MIP4=n \
	CONFIG_TOUCHSCREEN_RM_TS=n \
	CONFIG_TOUCHSCREEN_SILEAD=n \
	CONFIG_TOUCHSCREEN_SIS_I2C=n \
	CONFIG_TOUCHSCREEN_STMFTS=n \
	CONFIG_TOUCHSCREEN_SUN4I=n \
	CONFIG_TOUCHSCREEN_SURFACE3_SPI=n \
	CONFIG_TOUCHSCREEN_ZET6223=n \
	CONFIG_TOUCHSCREEN_IQS5XX=n \
	CONFIG_TOUCHSCREEN_GT9XXNEW_TS=m \
	CONFIG_TOUCHSCREEN_GT9XXNEWDUP_TS=n
  FILES:=$(LINUX_DIR)/drivers/input/init-input.ko
  FILES+=$(LINUX_DIR)/drivers/input/touchscreen/gt9xxnew/gt9xxnew_ts.ko
ifeq ($(CONFIG_PACKAGE_kmod-sunxi-i2c), y)
  FILES+=$(LINUX_DIR)/drivers/i2c/i2c-core.ko
endif
  AUTOLOAD:=$(call AutoProbe,gt9xxnew_ts)
endef

define KernelPackage/touchscreen-gt9xxnew/description
 Enable support for gt9xxnew touchscreen port.
endef
$(eval $(call KernelPackage,touchscreen-gt9xxnew))

define KernelPackage/gpadc_key
  SUBMENU:=$(INPUT_MODULES_MENU)
  TITLE:=gpadc_key support
  DEPENDS:= +kmod-input-core
  KCONFIG:= \
	CONFIG_INPUT_SENSOR=y \
	CONFIG_SUNXI_GPADC=m
  FILES:=$(LINUX_DIR)/drivers/input/sensor/sunxi_gpadc.ko
  AUTOLOAD:=$(call AutoProbe,gpadc_key)
endef

define KernelPackage/gpadc_key/description
 Enable support for gpadc_key port.
endef
$(eval $(call KernelPackage,gpadc_key))

define KernelPackage/sunxi-usb
  SUBMENU:=$(USB_MENU)
  TITLE:=sun20iw1 usb support
  KCONFIG:= \
	CONFIG_USB_SUPPORT=y \
	CONFIG_USB=y \
	CONFIG_USB_DEFAULT_PERSIST=y \
	CONFIG_USB_EHCI_HCD=y \
	CONFIG_USB_EHCI_ROOT_HUB_TT=y	\
	CONFIG_USB_EHCI_TT_NEWSCHED=y	\
	CONFIG_USB_EHCI_HCD_SUNXI=m \
	CONFIG_USB_OHCI_HCD=y	\
	CONFIG_USB_OHCI_HCD_SUNXI=m	\
	CONFIG_USB_SUNXI_HCD=m	\
	CONFIG_USB_SUNXI_HCI=m	\
	CONFIG_USB_SUNXI_EHCI0=m	\
	CONFIG_USB_SUNXI_EHCI1=m	\
	CONFIG_USB_SUNXI_OHCI0=m	\
	CONFIG_USB_SUNXI_OHCI1=m	\
	CONFIG_USB_GADGET=m		\
	CONFIG_USB_SUNXI_USB=m	\
	CONFIG_USB_ROLE_SWITCH=m
	
  FILES:=$(LINUX_DIR)/drivers/usb/host/ehci-hcd.ko
  FILES+=$(LINUX_DIR)/drivers/usb/host/ehci-sunxi.ko
  FILES+=$(LINUX_DIR)/drivers/usb/host/ohci-hcd.ko
  FILES+=$(LINUX_DIR)/drivers/usb/host/ohci-sunxi.ko
  FILES+=$(LINUX_DIR)/drivers/usb/host/sunxi-hci.ko
  FILES+=$(LINUX_DIR)/drivers/usb/gadget/function/usb_f_serial.ko
  FILES+=$(LINUX_DIR)/drivers/usb/gadget/function/u_serial.ko
  FILES+=$(LINUX_DIR)/drivers/usb/gadget/function/usb_f_fs.ko
  FILES+=$(LINUX_DIR)/drivers/usb/gadget/libcomposite.ko
  FILES+=$(LINUX_DIR)/drivers/usb/gadget/udc/udc-core.ko
  FILES+=$(LINUX_DIR)/drivers/usb/roles/roles.ko
  FILES+=$(LINUX_DIR)/drivers/usb/sunxi_usb/sunxi_usb_udc.ko
  FILES+=$(LINUX_DIR)/drivers/usb/sunxi_usb/sunxi_usbc.ko
endef

define KernelPackage/sunxi-usb/description
  Kernel modules for sun20iw1-usb support
endef
$(eval $(call KernelPackage,sunxi-usb))

define KernelPackage/sunxi-sound
  SUBMENU:=$(SOUND_MENU)
  TITLE:=sun20iw1 sound support
  KCONFIG:= \
	CONFIG_SOUND=y \
	CONFIG_SND=y \
	CONFIG_SND_SOC=y \
	CONFIG_SND_SUNXI_SOC_SUN20IW1_CODEC=m \
	CONFIG_SND_SUNXI_SOC_SIMPLE_CARD=m\
	CONFIG_SND_SUNXI_SOC_DAUDIO=m
  FILES:=$(LINUX_DIR)/drivers/base/regmap/regmap-mmio.ko
  FILES+=$(LINUX_DIR)/sound/soc/sunxi/snd-soc-sunxi.ko
  FILES+=$(LINUX_DIR)/sound/soc/sunxi/sun20iw1-sndcodec.ko
  FILES+=$(LINUX_DIR)/sound/soc/sunxi/snd-soc-sunxi-daudio.ko
  FILES+=$(LINUX_DIR)/sound/soc/sunxi/sun20iw1-codec.ko
  FILES+=$(LINUX_DIR)/sound/soc/sunxi/snd-soc-sunxi-dummy-cpudai.ko
  FILES+=$(LINUX_DIR)/sound/soc/sunxi/snd-soc-sunxi-simple-card.ko
  FILES+=$(LINUX_DIR)/sound/soc/generic/snd-soc-simple-card-utils.ko
endef

define KernelPackage/sunxi-sound/description
  Kernel modules for sun20iw1-sound support
endef
$(eval $(call KernelPackage,sunxi-sound))

define KernelPackage/sunxi-cedar
  SUBMENU:=$(OTHER_MENU)
  TITLE:=sunxi cedar support
  KCONFIG:= \
	CONFIG_MEDIA_SUPPORT=y	\
	CONFIG_VIDEO_ENCODER_DECODER_SUNXI=m
  FILES:=$(LINUX_DIR)/drivers/media/cedar-ve/sunxi-ve.ko
endef

define KernelPackage/sunxi-cedar/description
  Kernel modules for sunxi-cedar support
endef
$(eval $(call KernelPackage,sunxi-cedar))

define KernelPackage/sunxi-i2c
  SUBMENU:=$(I2C_MENU)
  TITLE:=sunxi i2c support
  KCONFIG:= \
	CONFIG_I2C=m	\
	CONFIG_I2C_COMPAT=y	\
	CONFIG_I2C_CHARDEV=m	\
	CONFIG_I2C_MUX=m	\
	CONFIG_I2C_HELPER_AUTO=y
  FILES:=$(LINUX_DIR)/drivers/i2c/i2c-mux.ko
  FILES+=$(LINUX_DIR)/drivers/i2c/i2c-dev.ko
  FILES+=$(LINUX_DIR)/drivers/i2c/i2c-core.ko
  FILES+=$(LINUX_DIR)/drivers/i2c/busses/i2c-sunxi.ko
  #FILES+=$(LINUX_DIR)/drivers/i2c/busses/i2c-gpio.ko
endef

define KernelPackage/sunxi-cedar/description
  Kernel modules for sunxi-cedar support
endef
$(eval $(call KernelPackage,sunxi-i2c))
