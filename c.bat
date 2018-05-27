@ECHO OFF
dmc %1
del %1.map
del %1.obj
move %1.exe bin\%1.exe
CLS
bin\%1.exe
