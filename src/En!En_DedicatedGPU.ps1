$ScriptDir = Split-Path $script:MyInvocation.MyCommand.Path
$ScriptDirChanged = $ScriptDir.replace('src','externals')

Import-Module -Name $ScriptDirchanged\DeviceManagement\Release\DeviceManagement.psd1 -Verbose

$Enable = Get-ChildItem args[0]

if($Selection)
{
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
}
else
{
    Write-Host "No Operation Selected!"
}
