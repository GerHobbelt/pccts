rem
rem create distribution files for www.hebbut.net
rem
                          
set name=pccts-1.33MR33.i_a
                                                       
mkdir ..\distrib

pushd ..\distrib

del *.bak
for %%f in ( *.exe *.tar *.z *.bz2 ) do move "%%f" "%%f.bak"

del *.exe 
del *.tar
del *.bz2

popd

                                                       
rem create rar files for the source dists, etc.

"c:\Program Files\WinRAR\Rar.exe" a -sfx -av -m5 -mdG -r -s ..\distrib\%name%.full-src.exe *.* README-PCCTS-1.33IA-MR33.TXT
"c:\Program Files\WinRAR\Rar.exe" a -sfx -av -m5 -mdG -r -s ..\distrib\cperf-2.1a.full-src.exe cperf-2.1a\*.* README-PCCTS-1.33IA-MR33.TXT
"c:\Program Files\WinRAR\Rar.exe" a -sfx -av -m5 -mdG -r -s ..\distrib\%name%.src.exe pccts\*.* README-PCCTS-1.33IA-MR33.TXT
"c:\Program Files\WinRAR\Rar.exe" a -sfx -av -m5 -mdG -r -s ..\distrib\%name%.mysamples-src.exe scripting\*.* testcase\*.* README-PCCTS-1.33IA-MR33.TXT
"c:\Program Files\WinRAR\Rar.exe" a -sfx -av -m5 -mdG -r -s ..\distrib\%name%.bin-win32.exe pccts\bin\*.* README-PCCTS-1.33IA-MR33.TXT
                                                          
                                                          
rem use the tar from UnxUtils: unix utils for win32 at sourgeforce; NO cygwin s***!

tar cvpf ..\distrib\%name%.full-src.tar * README-PCCTS-1.33IA-MR33.TXT
tar cvpf ..\distrib\cperf-2.1a.full-src.tar cperf-2.1a README-PCCTS-1.33IA-MR33.TXT
tar cvpf ..\distrib\%name%.src.tar pccts README-PCCTS-1.33IA-MR33.TXT
tar cvpf ..\distrib\%name%.mysamples-src.tar scripting testcase README-PCCTS-1.33IA-MR33.TXT
tar cvpf ..\distrib\%name%.bin-win32.tar pccts/bin README-PCCTS-1.33IA-MR33.TXT
                                         
                                         
pushd ..\distrib

for %%f in ( *.tar ) do bzip2 -z -9 "%%f"

popd
