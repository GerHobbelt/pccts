@echo on
rem profile batchfile with special settings: dumps report to tab-separated file for upload into Excel.

rem set path=%path%;"c:\program files\devstudio\vc\bin"
rem echo %path%

rem set farg=c:\prj_vc\projects\scripting\sample.sc
set farg=%2

echo ------------------------------------------------------------------ > output.profile.txt

script.exe "%farg%" "%3" "%4" "%5" "%6" "%7" "%8" "%9" >> output.profile.txt

echo ------------------------------------------------------------------ >> output.profile.txt

echo ------------------------------------------------------------------ >> output.profile.txt


"C:\Program Files\DevStudio\VC\bin\prep" /om /ft  script

rem "C:\Program Files\DevStudio\VC\bin\profile" /nc script %farg% %3 %4 %5 %6 %7 %8 %9

"C:\Program Files\DevStudio\VC\bin\profile" script %farg% %3 %4 %5 %6 %7 %8 %9 >> output.profile.txt
"C:\Program Files\DevStudio\VC\bin\prep" /m script
"C:\Program Files\DevStudio\VC\bin\plist" /t script >> upload.txt

echo ------------------------------------------------------------------ >> output.profile.txt



type output.profile.txt
type output.profile.txt >> cpuload.profile.txt
type output.profile.txt >> cpuload2.profile.txt
type output.profile.txt >> line.coverage.profile.txt
type output.profile.txt >> name.coverage.profile.txt

"C:\Program Files\DevStudio\VC\bin\plist" /sc script >> cpuload.profile.txt
"C:\Program Files\DevStudio\VC\bin\plist" script >> cpuload2.profile.txt
"C:\Program Files\DevStudio\VC\bin\plist" /sls script >> line.coverage.profile.txt
"C:\Program Files\DevStudio\VC\bin\plist" /sns script >> name.coverage.profile.txt

"C:\Program Files\DevStudio\VC\bin\plist" script


echo ------------------------------------------------------------------ 

