$ScriptDir = Split-Path $script:MyInvocation.MyCommand.Path
Import-Module -Name $ScriptDir\externals\DeviceManagement\Release\DeviceManagement.psd1 -Verbose
$Enable = Get-ChildItem args[0]

Write-Host $Enable

if($Enable -eq "1")
{
    Write-Host "Enable GPU"
    Get-Device | where {$_.name -like "NVIDIA GeForce*"} | Enable-Device
}
if($Enable -eq "0")
{
    Write-Host "Disable GPU"
    Get-Device | where {$_.name -like "NVIDIA GeForce*"} | Disable-Device
}
else
{
    Write-Host "No Operation Selected!"
}
