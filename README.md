# DedicatedGPUControl
Script to enable/disable dedicated GPU

## /lib
Contains the nvapi.dll which is used to get the gpu utilization of each card in the C++ script.

## /src
Contains the powershell script which is used to enable/disable the dedicated Nvidia GPU of the system.
Aswell as the C++ script which is based on the nv api.

## Future
Combining the ps script and the c++ script the get a gpu load based automated enable/disable script for dedicated Nvidia GPUs.

## Links(Inspiration)
http://read.pudn.com/downloads62/sourcecode/windows/comm/217489/%E6%93%8D%E4%BD%9C%E7%BD%91%E5%8D%A1/jyqywk.cpp__.htm
https://docs.microsoft.com/de-ch/windows-hardware/drivers/devtest/devcon
https://stackoverflow.com/questions/11178954/trying-to-disable-a-device-in-the-windows-environment
