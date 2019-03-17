@echo off
where g++>nul
cls
if errorlevel 1 (
echo gcc NOT FOUND in your computer!!
echo Press any key to start installation!
pause>nul
goto install
) else (
echo Detected gcc Environment..
echo Start to compile!!
goto compile
)



:install
cls
echo Please download and run the gcc install program.
ping 127.0.0.1 >nul
start https://yimian-setup.obs.myhwclouds.com/setup/tdm64-gcc-5.1.0-2.exe
ping 127.0.0.1 >nul
cls
echo After install, Please restart this script to compile!!&&pause&&exit


:compile
cls
echo compiling...
g++ -O2 -o same_vec same_vec.cpp
g++ -O2 -o Fraction_test Fraction_test.cpp Fraction.h
cls
echo compile finished! The program is in current folder!
pause

exit


