#include <linux/i2c.h>
#include <linux/export.h>
//#include <linux/mutex.h>
#include "sensor.h"
//DEFINE_MUTEX(mutex_client);
//static struct i2c_client *sensor_client=NULL;
struct i2c_client *sensor_i2c_register_device(int bus_no, int client_addr, const char *client_name)
{	
	struct i2c_adapter *adapter = NULL;
	struct i2c_client *sensor_client=NULL;
	
	struct i2c_board_info sensor_i2c_board_info = {
	.type          = "unused",
	.flags         = 0x00,
	.addr          = 0xff,
	.platform_data = NULL,
	.archdata      = NULL,
	.irq           = -1,
	};
	
	if ((bus_no<0) || (client_addr>0x7f) || (client_addr<0)|| (!client_name))
	{
		printk(KERN_ERR "%s param error! pls check out!\n", __FUNCTION__);
		return NULL;
	}
	printk(KERN_INFO "%s busno %d client_addr 0x%x client_name %s \n", __FUNCTION__, \
		bus_no, client_addr, client_name);
		
	sensor_i2c_board_info.addr = client_addr;
	//sensor_i2c_board_info.type = client_name;
	strcpy(sensor_i2c_board_info.type, client_name);
		
	adapter = i2c_get_adapter(bus_no);/*in bus NR*/

	if (NULL == adapter) {
		printk("can not get i2c adapter, client address error\n");
		return NULL;
	}
	
	//mutex_lock(&mutex_client);
	sensor_client = i2c_new_device(adapter, &sensor_i2c_board_info);
	
	
	if (sensor_client == NULL) {
		printk("allocate i2c client failed\n");
		//mutex_unlock(&mutex_client);
		return NULL;
	}
	i2c_put_adapter(adapter);
	//mutex_unlock(&mutex_client);
	
	return sensor_client;
}
EXPORT_SYMBOL(sensor_i2c_register_device);

struct i2c_client *sensor_i2c_register_device2(int bus_no, int client_addr, const char *client_name,void *pdata)
{	
	struct i2c_adapter *adapter = NULL;
	struct i2c_client *sensor_client=NULL;
	
	struct i2c_board_info sensor_i2c_board_info = {
	.type          = "unused",
	.flags         = 0x00,
	.addr          = 0xff,
	.platform_data = NULL,
	.archdata      = NULL,
	.irq           = -1,
	};
	
	if ((bus_no<0) || (client_addr>0x7f) || (client_addr<0)|| (!client_name))
	{
		printk(KERN_ERR "%s param error! pls check out!\n", __FUNCTION__);
		return NULL;
	}
	printk(KERN_INFO "%s busno %d client_addr 0x%x client_name %s \n", __FUNCTION__, \
		bus_no, client_addr, client_name);
		
	sensor_i2c_board_info.addr = client_addr;
	sensor_i2c_board_info.platform_data = pdata;
	//sensor_i2c_board_info.type = client_name;
	strcpy(sensor_i2c_board_info.type, client_name);
		
	adapter = i2c_get_adapter(bus_no);/*in bus NR*/

	if (NULL == adapter) {
		printk("can not get i2c adapter, client address error\n");
		return NULL;
	}
	
	//mutex_lock(&mutex_client);
	sensor_client = i2c_new_device(adapter, &sensor_i2c_board_info);
	
	
	if (sensor_client == NULL) {
		printk("allocate i2c client failed\n");
		//mutex_unlock(&mutex_client);
		return NULL;
	}
	i2c_put_adapter(adapter);
	//mutex_unlock(&mutex_client);
	
	return sensor_client;
}
EXPORT_SYMBOL(sensor_i2c_register_device2);

void sensor_i2c_unregister_device(struct i2c_client *client)
{
	if (client != NULL)
	{
		i2c_unregister_device(client);
	}
}
EXPORT_SYMBOL(sensor_i2c_unregister_device);

