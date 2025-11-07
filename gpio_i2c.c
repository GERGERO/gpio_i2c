#include <linux/platform_device.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/gpio/machine.h>
#include <linux/platform_data/i2c-gpio.h>


#define GPIO_I2C_SDA_PIN_NUM            2
#define GPIO_I2C_SCL_PIN_NUM            3
#define GPIO_I2C_DRIVER_NAME            "i2c-gpio"
#define GPIO_I2C_BUS_ID                 -1


static struct gpiod_lookup_table gpios_i2c_table = {
	.dev_id = "i2c-gpio",
	.table = {
		GPIO_LOOKUP_IDX("pinctrl-rp1", GPIO_I2C_SDA_PIN_NUM,
				NULL, 0, GPIO_OPEN_DRAIN),
		GPIO_LOOKUP_IDX("pinctrl-rp1", GPIO_I2C_SCL_PIN_NUM,
				NULL, 1, GPIO_OPEN_DRAIN),
		{}, /* Terminating entry GPIO_OPEN_DRAIN */
	}
};

static struct i2c_gpio_platform_data device_i2c_platdata = {
    .sda_is_open_drain  = 0,
    .scl_is_open_drain  = 0,
};


static void gpioi2c_device_release(struct device *dev)
{
    gpiod_remove_lookup_table(&gpios_i2c_table);
}


static struct platform_device gpio_i2c_device = {
    .name               = GPIO_I2C_DRIVER_NAME,
    .id                 = GPIO_I2C_BUS_ID,
	.dev                = {
        .platform_data  = &device_i2c_platdata,
		.release = gpioi2c_device_release,
	},

};


static int __init gpio_i2c_init(void)
{
    int ret;

	gpiod_add_lookup_table(&gpios_i2c_table);

	ret = platform_device_register(&gpio_i2c_device);
    if (ret)
        printk(KERN_ERR "gpio-i2c: device register failed: %d\n", ret);

    return ret;
}
subsys_initcall(gpio_i2c_init);


static void __exit gpio_i2c_exit(void)
{
	platform_device_unregister(&gpio_i2c_device);
    return ;
}
module_exit(gpio_i2c_exit);


MODULE_AUTHOR("Hyve");
MODULE_DESCRIPTION("Platform-independent GPIO I2C Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:gpio-i2c");