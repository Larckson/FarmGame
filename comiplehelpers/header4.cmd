"%TMP_OUT%" %*
set EC=%ERRORLEVEL%
del "%TMP_OUT%"
exit /b %EC%