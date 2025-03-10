Package/aic8800-firmware = $(call Package/firmware-default,AIC aic8800 firmware)

define Package/aic8800-firmware/install
	$(INSTALL_DIR) $(1)/$(FIRMWARE_PATH)
	$(INSTALL_DATA) $(TOPDIR)/package/firmware/linux-firmware/aic8800/*.bin $(1)/$(FIRMWARE_PATH)/
	$(INSTALL_DATA) $(TOPDIR)/package/firmware/linux-firmware/aic8800/aic_userconfig_8800d80.txt $(1)/$(FIRMWARE_PATH)/
endef
$(eval $(call BuildPackage,aic8800-firmware))


