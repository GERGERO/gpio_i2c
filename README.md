1. Check GPIO chip name and change it.
2. Choose two pins with open drain drivenable ability and config in C file.
   
pchuangb@raspberrypi:~ $ gpiodetect
gpiochip0 [pinctrl-rp1] (54 lines)
gpiochip10 [gpio-brcmstb@107d508500] (32 lines)
gpiochip11 [gpio-brcmstb@107d508520] (4 lines)
gpiochip12 [gpio-brcmstb@107d517c00] (17 lines)
gpiochip13 [gpio-brcmstb@107d517c20] (6 lines)
gpiochip0 [pinctrl-rp1] (54 lines)
