X:
CD\
net use Q: \\wexfs\users\ /user:REDMOND
call Q:\edrive\Register_WTT_Client.cmd
xcopy Q:\edrive X:\ /E /C /Y
net use /delete Q: