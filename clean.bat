@echo off
echo 正在清除垃圾文件，请稍等......

del /f/s/q/a *.obj
del /f/s/q/a *.pch
del /f/s/q/a *.idb
del /f/s/q/a *.pdb
del /f/s/q/a *.ncb 
del /f/s/q/a *.opt 
del /f/s/q/a *.plg
::del /f/s/q/a *.res
del /f/s/q/a *.sbr
del /f/s/q/a *.ilk
del /f/s/q/a *.aps
del /f/s/q/a *.suo
del /f/s/q/a *.exp
del /f/s/q/a *.bsc
del /f/s/q/a BuildLog.htm

echo 清除完毕！
echo. & pause