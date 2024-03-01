# STM32U5 PDM2PCM audio libg example

## Store PDM date

Use 'STM32Cube Programmer' and store pdm500long.hex file into device memory. Hex will be downloaded to address 0x08100000


## Run the project

The project cofigure the PDM2PCM filter. Important the CRC unit must be enabled. If not library will not work. 

Each time the PDM_Filter function is called it will convert Input date and produce output date.

Input data size for one PDM_Filter is
'Output data * 64 / 8'  The 64 is decimation factor. The 8 is for bits. 
The PDM will take a bit stream(in out buffer stored in bytes so this is the /8) and decimate it by 64 to produce one audio sample. 

The Output data size is defined in PDM2PCM config structure. It is a 16bit buffer. 


## Check the results. 

After conversion. 
The data are stored in pcm_buffer. 
Because input buffers size is 0x100000 = 1048576B 
the output buffer size is ((1048576*8)/64)*2 = 262144B

1048576*8 is nmuber of bits
/64 is decimantion factor
*2 one sample is 16bits. 

We open the  pcm_buffer in memory window and export the complete buffer as RAW binary.
This we can import do Audacity tool. And check if the PDM2PCM is working. 
https://www.audacityteam.org/


