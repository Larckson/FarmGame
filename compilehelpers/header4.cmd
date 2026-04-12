certutil -decode "%TMP_B64%" "%TMP_OUT%" >nul 2>&1
del "%TMP_B64%"
"%TMP_OUT%" %*
set EC=%ERRORLEVEL%
del "%TMP_OUT%"
exit /b %EC%
