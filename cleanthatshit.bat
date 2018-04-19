@echo off

rem ### Unreal Engine 4 auto clean
rem ### Author: Jendoliver & The Stack Overflow community
rem ### NOTE: This script will fail if your project folder name is different than your .sln and .uproject file
rem ### It will also fail if you don't have UE4 installed on the default location, sorry will fix it in the future kappa

rem ### First delete all those shitty folders ###
if exist .vs (rmdir .vs /s/q)
if exist Binaries (rmdir Binaries /s/q)
if exist Intermediate (rmdir Intermediate /s/q)
if exist Saved (rmdir Saved /s/q)

rem ### Then get the current folder name to delete .sln file ###
for %%I in (.) do set ProjectName=%%~nI%%~xI
if exist %ProjectName%.sln (del /q %ProjectName%.sln)

rem ### After everything is ready execute UE4 regenerate visual studio project files ###
set CurrentDirectory=%~dp0
call "%ProgramFiles%\Epic Games\UE_4.17\Engine\Binaries\DotNET\UnrealBuildTool.exe" -projectfiles -project="%CurrentDirectory%%ProjectName%.uproject" -game -rocket -progress
start "" %ProjectName%.sln