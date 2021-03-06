# Smart Water Supply System for Agriculture

## Introduction

* This repository includes all the project files related to the development of a smart water supply system for agriculture for EN2560 -  Internet of Things Design and Competition module in department of Electronic and Telecommunication Engineering.
* This system can monitor the soil moisture, temperature, and humidity from the sensors in the farm. We are using the Watson IoT Simulator to get the Temperature,Humidity and Soil Moisture values.
* The farmer can also get the realtime weather forecasting data of the location of the farm by using OpenWeatherMap API.
* The farmer can control the watering system via dashboard, via voice command, via webpage or via the blynk app from anywhere at anytime. 

## Watson IoT Sensor Simulator

* For the simulation purposes, here we use [IBM IoT Sensor Simulator](https://watson-iot-sensor-simulator.mybluemix.net/) for monitoring the farm. To connect to this simulator, the user needs to enter the device information created. Here we can change the values using up and down arrows.

![](Images/IoTSimulator.png)

## Dashboard

* The collected data from the sensor simulator and [OpenWeatherMap API](https://home.openweathermap.org/users/sign_in) is viewed in the dashboard. From the buttons, the motor can be turned on and off.
* To visit the dashboard, [click here](https://smartagricultureapp.mybluemix.net/ui)
![](Images/dashboard.png)

## Inputs

* User can set the location by giving the coordinates or the city/country. Also can set the limits of the sensor as required using the sliding bars. 
![](Images/settings.png)

## Node-Red Program Flow

* The designed flow is shown below you can view it [here](NodeREDflows.json)
![](Images/NodeRed.png)

## Different motor controlling mwthods

* The farmer can control the watering system via [dashboard](https://smartagricultureapp.mybluemix.net/ui), via voice commands, via webpage or via the blynk app from anywhere at anytime. 
![](Images/Controling%20modes.png)

### Group Members

1. [Muhammad Aqeel](https://github.com/AqeelMuhammad)
1. [Navindu Rasanjana](https://github.com/NavinduRasanjana)
1. [Tharuka Nilupul](https://github.com/TharukaN17)

* For demostration Videos [click here](https://youtube.com/playlist?list=PL8BtMKbBdoseuaje2f-dUfK9YvDc6sRkN)
