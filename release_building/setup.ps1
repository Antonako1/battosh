# setup.ps1

# Check if the script is running with administrative privileges
$isAdmin = ([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)

if (-not $isAdmin) {
    # Relaunch the script with administrative privileges
    Start-Process powershell -Verb RunAs -ArgumentList ("-NoProfile -ExecutionPolicy Bypass -File `"$($MyInvocation.MyCommand.Path)`"")
    exit
}

# Define the path to the battosh folder
$battoshFolderPath = "$PSScriptRoot"

# Check if battosh folder path is already in the system's PATH environment variable
$currentPath = [System.Environment]::GetEnvironmentVariable("PATH", [System.EnvironmentVariableTarget]::Machine)
if ($currentPath -split ";" -notcontains $battoshFolderPath) {
    # Add the battosh folder to the system's PATH environment variable
    $newPath = $currentPath + ";" + $battoshFolderPath
    [System.Environment]::SetEnvironmentVariable("PATH", $newPath, [System.EnvironmentVariableTarget]::Machine)
    Write-Host "battosh folder added to the system PATH."
} else {
    Write-Host "battosh folder is already present in the system PATH."
}
