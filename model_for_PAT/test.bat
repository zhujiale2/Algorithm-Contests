:loop
generator.exe > input
force.exe < input > stdout
kd-Tree.exe < input > myout
fc stdout myout
if not errorlevel 1 goto loop