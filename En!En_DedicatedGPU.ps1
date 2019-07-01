$ScriptDir = Split-Path $script:MyInvocation.MyCommand.Path
Import-Module -Name $ScriptDir\externals\DeviceManagement\Release\DeviceManagement.psd1 -Verbose
Set-ExecutionPolicy RemoteSigned
Write-Host "Dedicated GPU enable/disable PowerShell Script"
$Selection = Read-Host -Prompt 'Select GPU state [enable/disable]'
if($Selection)
{
    if($Selection -eq "enable")
    {
        Write-Host "Enable GPU"
        Get-Device | where {$_.name -like "NVIDIA GeForce*"} | Enable-Device
    }
    if($Selection -eq "disable")
    {
        Write-Host "Disable GPU"
        Get-Device | where {$_.name -like "NVIDIA GeForce*"} | Disable-Device
    }
    else
    {
        Write-Host "No Operation Selected!"
    }
}
else
{
    Write-Host "No Operation Selected!"
}