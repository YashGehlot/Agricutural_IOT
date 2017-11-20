# Agricutural_IOT

ABSTRACT
"Agricultural IOT" is a system that is developed to make life of a farmer easier in terms of soil analysis and requirements of the crops. It gathers of the the environmental conditions that are prevalent in the field as well as the storage areas.This data is gathered at multiple points in the field. Then, the data is conveyed to a central node using mesh networking among the nodes.At the central node the data is then uploaded to the server using a GSM module. The system uses this data to inform the farmer the requirements of the crop that would eventually lead to the enhancement of the crop yield.


CONTENTS
Abstract										        
Content										           
Introduction  									    
Background of Project								
System Architecture								  
Role of Each Node in the System			
Components of Individual Nodes			
Circuit diagrams									 




INTRODUCTION
The Internet of Things (IoT) is the inter-networking of physical devices, vehicles (also referred to as "connected devices" and "smart devices"), buildings, and other items embedded with electronics, software, sensors, actuators, and network connectivity which enable these objects to collect and exchange data. The IoT allows objects to be sensed or controlled remotely across existing network infrastructure, creating opportunities for more direct integration of the physical world into computer-based systems, and resulting in improved efficiency, accuracy and economic benefit in addition to reduced human intervention. When IoT is augmented with sensors and actuators, the technology becomes an instance of the more general class of cyber-physical systems, which also encompasses technologies such as smart grids, virtual power plants, smart homes, intelligent transportation and smart cities. 
Our system is an IOT based system designed with the following specification:
Continuous monitoring: The System tracks soil moisture, temperature, humidity, gas content(for storage).
Real-time guidance: The System provides real time notification to the farmer based on the farm conditions.
Region specific guidance: The System provides notification as to the requirements of the different regions of the field.
Data preservation: The System stores the data of the farm on an online server, which can be used for  analysis of soil over a large region, crop yield prediction, predicting the crop best compatible with climatic as well as soil conditions. 


BACKGROUND OF THE PROJECT
Agriculture plays an important role in our country, with about 70% of population depending upon farming as their livelihood and one third of the nation’s capital coming from farming. Growth in agricultural sector is necessary for the development of economic condition of the country. Being of such importance any problem concerning agriculture hinders the development of the country. Hence this project aims at monitoring the field in real time and providing the data to farmers or even predict specific problem that may occur if some action is not taken in time.
3 major problems are targeted :
Inefficient Irrigation :
As urban and other demands multiply, less water is likely to be available for irrigation. In parts of India, the over-pumping of water for agricultural use is leading to failing groundwater levels.
Conversely, water-logging is leading to the build-up of salts in the soils of some irrigated areas.
Storage Problem
There is enough food in India to feed everyone, but wastage of large amounts of food prevents this from happening.
1.06 Lac tones of wheat under the custody of State Government Agencies in Haryana and Punjab was damaged in March 2012. Which could easily feed 1 lakh family for 3 years (30kg per family per month).
Lack of Information to farmers
The biggest problem that farmers in India face is Lack of access to information. Majority of farmers are relying on traditional methods of farming and get very less support from government agriculture department
The most popular source of information for them is input dealer
Most of the time they tend to impose their products on the farmer. Farmers are forced to buy these overpriced and ineffective products due to lack of knowledge.
And these same dealers set them up to sell their crops at throwaway prices.


SYSTEM ARCHITECTURE
The complete system “Agricultural IoT” consists of a number of individual nodes(field nodes) that gather data at that point of the field. This data is then sent to a central node named as “data node” via shortest path in the network available at that point of time.
This network that we have created is using esp8266 module. These esps communicate with each other using wifi signals. The esps gather the different sensors data and then transfer it. 
A SIM card enabled Data hub is placed in the field anywhere near the mesh so as to collect all the data from each and every node and each and every sensor. The Data hub consists of ESP8266, Arduino, GSM module.
The collected data is uploaded to the servers for further processing with respect to crops. Once the the data has been processed the farmer is notified via SMS to take necessary action. 
![image](https://github.com/YashGehlot/Agricutural_IOT/blob/master/image.png)


ROLE OF EACH NODE IN THE SYSTEM
Soil Moisture: The full volume of the soil can be broken down into soil particles, roots, air, and liquid water the coats the soil particles.The soil moisture sensor sends electrical impulses and measures the conductivity of the soil which in turn is related to the moisture content of the soil.
Water is an important necessity for the plants so proper care must be taken to fulfill the crop requirements. It is also to not that the field must not be flooded with water as crops are damaged.The management of the requirements of the water is done by FarmAssist.
Temperature: The temperature readings of the nodes are much more localized that the weather forecast and provide a sense of the temperature variation in the field. The weather forecast temperature is typically a measure of the air temperature several feet above the ground which is of no significant use to the farmer.
Humidity: The humidity is sometimes an under-appreciated variable for the farmers.Water evaporates through the pores of the leaves which are open to take in carbon dioxide.A low humidity means a lot of water can be lost through evapotranspiration, which means the plants will require more water.
Gas Concentration(for storage): In the storage areas the gas sensors are used to measure the amount of methane and smoke. Methane is released when the food rots.In order to check the quality of harvested crop, methane sensors are used.The smoke sensors are used for detecting fire in the storage area.

COMPONENTS OF INDIVIDUAL NODE

Esp8266:The ESP8266 is a low-cost Wi-Fi chip with full TCP/IP stack and MCU (microcontroller unit) capability.
![image](https://github.com/YashGehlot/Agricutural_IOT/blob/master/esp.jpg)

Soil Moisture Sensor: Measures the volumetric water content in the soil.
![image](https://github.com/YashGehlot/Agricutural_IOT/blob/master/soil%20moist.jpg)

Gas Sensors (MQ2 and MQ4): MQ2 is a smoke sensor and MQ4 is methane sensor.
![image](https://github.com/YashGehlot/Agricutural_IOT/blob/master/gas%20sensor.jpg)

DHT11: The DHT11 is a basic, ultra low-cost digital temperature and humidity sensor. It uses a capacitive humidity sensor and a thermistor to measure the surrounding air, and spits out a digital signal on the data pin (no analog input pins needed). 
Its fairly simple to use, but requires careful timing to grab data. The only real downside of this sensor is you can only get new data from it once every 2 seconds, so when using our library, sensor readings can be up to 2 seconds old.
![image](https://github.com/YashGehlot/Agricutural_IOT/blob/master/dht11.jpg)


CIRCUIT DIAGRAMS
FIGURE : STORAGE NODE
![image](https://github.com/YashGehlot/Agricutural_IOT/blob/master/storageNode.png)

FIGURE : FIELD NODE
![image](https://github.com/YashGehlot/Agricutural_IOT/blob/master/fieldNode.png)

FIGURE : DATA NODE
![image](https://github.com/YashGehlot/Agricutural_IOT/blob/master/dataNode.png)
