# Teensy-Controller
This project aims at building a cost effective toolbox for active acoustic control, whether it is to solve physical problems (noise control, active metamaterials..) or for audio applications. For this targeted applications, it is expected that the system obtains some physical analog inputs and output an analog treated version of the input.  


To ensure sufficient performances and minimal delay, we will use the Teensy 4.1 microcontroller and build all the necessary circuitery (level shift, analog conversion...) and codes. This work is split as follow:
* Analog output using the MCP4822 via the SPI interface.
* Simultenous reading (internal ADC) and writing (MCP4822)
* Conditionning of the analog input (1.65 DC offset and clamping)

# External DAC
<p align="center">
  <img src="DAC/Teensy_DAC_schematic.png" width="500"><br>
  <em> Figure 1: Sketch of the circuit using the MCP4822. Each output of the DAC is connected to a different terminal. One output corresponds to the raw signal while the second is filtered (High pass RC filter).  </em>
</p>

Using the MCP4822 with a Teensy is relatively easy using the SPI interface. In fact, there is several online tutorials covering this topic (using arduino/ESP32..). The circuit used in this work is given in Figure 1. Both outputs are used, one  corresponds to the raw DAC output signal while the second is filtered using a simple low pass RC filter.

# Input-Output

<p align="center">
  <img src="DAC/PCB_V1.MP.jpg" width="500"><br>
  <em> Figure 2: Version 1 of the controller (corresponds to the sketch in Figure 1).  </em>
</p>

A first PCB (Figure 2)  was printed following the schematic in Figure 1. While not perfect, it is sufficient to ensure better connection between the components, reduces the amounts of cables, and improve stability. The design will be improved at a later stage when this work have sufficiently advanced (e.g. better bypass, more pins for the teensy, reduces the traces length, include the offset and clamping circuit for the inputs, BNC terminals...)  

First step, we will couple the Teensy with a MCP4822 (DAC) to convert the digital output to an analog signal.
<p align="center">
  <img src="DAC/Delay.jpg" width="500"><br>
  <em>Figure 2: Input (Frequency generator) vs Output (MCP4822 Output) for different frequencies. </em>
</p>

The MCP4822 is controlled via the SPI interface and allows relatively decent performances, atleast in the audio range. For instance, the total delay measured between the the frequency generator and the output of the MCP is estimated to 2us (See Fig.1 for some measured signals).

Note that the input analog signal is read via the native ADC.


