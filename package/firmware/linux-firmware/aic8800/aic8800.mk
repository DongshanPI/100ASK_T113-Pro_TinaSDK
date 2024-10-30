Package/aic8800-firmware = $(call Package/firmware-default,AIC aic8800 firmware)

define Package/aic8800-firmware/install
	$(INSTALL_DIR) $(1)/$(FIRMWARE_PATH)
	$(INSTALL_DATA) $(TOPDIR)/package/firmware/linux-firmware/aic8800/fmacfw.bin $(1)/$(FIRMWARE_PATH)/fmacfw.bin
	$(INSTALL_DATA) $(TOPDIR)/package/firmware/linux-firmware/aic8800/fmacfw_usb.bin $(1)/$(FIRMWARE_PATH)/fmacfw_usb.bin
	$(INSTALL_DATA) $(TOPDIR)/package/firmware/linux-firmware/aic8800/fmacfw_rf.bin $(1)/$(FIRMWARE_PATH)/fmacfw_rf.bin
	$(INSTALL_DATA) $(TOPDIR)/package/firmware/linux-firmware/aic8800/fmacfw_rf_usb.bin $(1)/$(FIRMWARE_PATH)/fmacfw_rf_usb.bin
	$(INSTALL_DATA) $(TOPDIR)/package/firmware/linux-firmware/aic8800/fw_adid.bin $(1)/$(FIRMWARE_PATH)/fw_adid.bin
	$(INSTALL_DATA) $(TOPDIR)/package/firmware/linux-firmware/aic8800/fw_adid_u03.bin $(1)/$(FIRMWARE_PATH)/fw_adid_u03.bin
	$(INSTALL_DATA) $(TOPDIR)/package/firmware/linux-firmware/aic8800/fw_patch.bin $(1)/$(FIRMWARE_PATH)/fw_patch.bin
	$(INSTALL_DATA) $(TOPDIR)/package/firmware/linux-firmware/aic8800/fw_patch_u03.bin $(1)/$(FIRMWARE_PATH)/fw_patch_u03.bin
	$(INSTALL_DATA) $(TOPDIR)/package/firmware/linux-firmware/aic8800/fw_patch_table.bin $(1)/$(FIRMWARE_PATH)/fw_patch_table.bin
	$(INSTALL_DATA) $(TOPDIR)/package/firmware/linux-firmware/aic8800/fw_patch_table_u03.bin $(1)/$(FIRMWARE_PATH)/fw_patch_table_u03.bin
	$(INSTALL_DATA) $(TOPDIR)/package/firmware/linux-firmware/aic8800/aic_userconfig.txt $(1)/$(FIRMWARE_PATH)/aic_userconfig.txt
endef
$(eval $(call BuildPackage,aic8800-firmware))


