@ECHO OFF
cd /d %~dp0
ECHO Setting global variables...

FOR %%A IN ("%~dp0.") DO SET "ROOTPATH=%%~dpA"
set "TOOLSPATH=C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools"
set "CMAKEPATH=C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\2022\COMMUNITY\COMMON7\IDE\COMMONEXTENSIONS\MICROSOFT\CMAKE"
set "NINJAPATH=C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\2022\COMMUNITY\COMMON7\IDE\COMMONEXTENSIONS\MICROSOFT\CMAKE\Ninja"
set "PROJECTNAME=battosh" :: Place here the same name you have in CMakelists.txt (project_name)
set "COMPILERPATH=cl.exe"

ECHO Done.

