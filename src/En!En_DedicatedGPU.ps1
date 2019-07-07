$ScriptDir = Split-Path $script:MyInvocation.MyCommand.Path
Import-Module -Name $ScriptDir\externals\DeviceManagement\Release\DeviceManagement.psd1 -Verbose
#Set-ExecutionPolicy unregistered

$computer = $env:COMPUTERNAME
$namespace = "ROOT\cimv2\mdm"
$gpuclass = "Gpu"
$GPU_Meters=Get-WmiObject -Class $gpuclass -ComputerName $computer -Namespace $namespace | Select-Object *
#$GPU_Meters=Get-WmiObject -Class $gpuclass -ComputerName $computer | Select-Object *


$VRamUsage = Get-WmiObject Win32_VideoController -filter "name like '%NVIDIA%'" | select AdapterRAM #,@{Expression={$_.adapterram/1MB};label="MB"}
$AcceleratorCapabilities = Get-WmiObject Win32_VideoController -filter "name like '%NVIDIA%'" | select AcceleratorCapabilities,@{Expression={$_.AcceleratorCapabilities};label="1"}
Write-Host "$VRamUsage"

#$nvidia_model=$GPU_Meters.productName
#$gpu_usage=$GPU_Meters.percentGpuUsage
#Write-Host "$nvidia_model%"

#Write-Host "Dedicated GPU enable/disable PowerShell Script"
#$Selection = Read-Host -Prompt 'Select GPU state [enable/disable]'
#if($Selection)
#{
#    if($Selection -eq "enable")
#    {
#        Write-Host "Enable GPU"
#        Get-Device | where {$_.name -like "NVIDIA GeForce*"} | Enable-Device
#    }
#    if($Selection -eq "disable")
#    {
#        Write-Host "Disable GPU"
#        Get-Device | where {$_.name -like "NVIDIA GeForce*"} | Disable-Device
#    }
#    else
#    {
#        Write-Host "No Operation Selected!"
#    }
#}
#else
#{
#    Write-Host "No Operation Selected!"
#}