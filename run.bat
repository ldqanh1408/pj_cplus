@echo off

:: Di chuyển đến thư mục chứa file .bat
cd /d "%~dp0"

:: Biên dịch chương trình
g++ -o main main.cpp -static

:: Chạy chương trình
main.exe
pause