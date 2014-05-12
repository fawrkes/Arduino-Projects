Weather Display
=======

Numeric weather data representation is a relic of a time gone by. Smartphones, websites, and various weather instruments represent weather data in an inaccessible almost archaic way via simple numeric characters. Especially early in the morning or late at night, when it is difficult to quickly register this information, a more abstract graphical representation of these data is needed. We looked to design a way of graphically displaying current and forecasted (via the internet) weather information. Technological interfaces were initially developed to be simple and straightforward but, if engineered correctly, can completely change the users experience of the technology, which is what this project was meant to do.

Data representation and visualization is fast becoming a dynamic and interesting technological problem. Data can take on a completely different form and meaning when it represented visually; this makes it more accessible, allows for greater insight, and make for a much more enjoyable experience. This project aimed to make progress towards better graphical displays of useful data and to provide a remedy to constant misinterpretations of forecasted weather data. Weather data, much like any other, has always been represented in a purely numeric fashion; the farthest people have gone to represent it in any graphical way has been through standardized .png images of clouds or through colors. We wanted to create a more creative and dynamic representation that provided an instinctive and intuitive understanding of the weather without having to think very much. We also wanted to provide a way for the user to forecast the weather conditions (using the same graphical methods) so that they can make accurate decisions about their day.

From the graphical standpoint, we chose the medium of an LED matrix to use in this graphical representation because it allowed for enough flexibility to configure it as we wanted to and it allowed for enough standardization that we knew it could be easily created and/or mass produced. So, we set out to associated characteristics of the LED matrix with characteristics of the weather. 

For example, we started out with four main weather characteristics (and associations):

	Sound: number of LEDs lit (in the Y direction)
	Ambient Light: brightness of all the LEDs
	Humidity: blinking rate of LEDs
	Temperature: relative brightness of Red/Green LEDs (dual-color display)

All of these characteristics would be inputted via analog sensors and multiplexed with the forecasted weather inputted from a micro-controller. Each of these signals would then be conditioned (via analog circuitry) and then mapped onto the LED matrix display simultaneously. Essentially, we used the approach of building an analog-to-digital and analog-to-analog converters that process the sensor input and produced some output analog effect on the LED matrix.

The core components of the design were signal processing circuits for each of the analog sensors, a series of switches and drivers to drive the LED matrix, and a series of digital Mutilplexers used to alternate between the current and forecasted data. Specifically, we ordered four analog sensors, a dual-color LED matrix, and an Arduino LED matrix serial interface. However, our design was massively crippled as the LED matrix (and serial interface) and two of the sensors never arrived, so we had to use spare parts that we could find. Especially because some of our designed systems were heavily integrated with one another, it was difficult to successfully implement them because of our missing parts.

