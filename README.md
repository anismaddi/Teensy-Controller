# Teensy-Controller
This project aims at building a cost effective toolbox for active acoustic control, whether it is to solve physical problems (noise control, active metamaterials..) or for audio applications. For this targeted applications, it is expected that the system obtains some physical analog inputs and output an analog treated version of the input.  


To ensure sufficient performances and minimal delay, we will use the Teensy 4.1 microcontroller and build all the necessary circuitery (level shift, analog conversion...) and codes. This work is split as follow:
* Analog output using the MCP4822 via the SPI interface.
* Simultenous reading (internal ADC) and writing (MCP4822)
* Conditionning of the analog input (level shift)

# Input-Output Response

First step, we will couple the Teensy with a MCP4822 (DAC) to convert the digital output to an analog signal.
<p align="center">
  <img src="DAC/Delay.jpg" width="500"><br>
  <em>Fig1: Input (Frequency generator) vs Output (MCP4822 Output) for different frequencies. </em>
</p>

The MCP4822 is controlled via the SPI interface and allows relatively decent performances, atleast in the audio range. For instance, the total delay measured between the the frequency generator and the output of the MCP is estimated to 2us (See Fig.1 for some measured signals).

Note that the input analog signal is read via the native ADC.

<p align="center">
  <img src="DAC/Teensy_DAC_schematic.png" width="500"><br>
  <em> Sketch of the circuit using the MCP4822. Each output of the DAC is connected to a female BNC connector. One output corresponds to the raw signal while the second is filtered (High pass RC filter).  </em>
</p>
