#!/bin/sh
bindir=$(pwd)
cd /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/TP/
export 

if test "x$1" = "x--debugger"; then
	shift
	if test "xYES" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		/usr/bin/gdb -batch -command=$bindir/gdbscript --return-child-result /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/build/TP 
	else
		"/home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/build/TP"  
	fi
else
	"/home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/build/TP"  
fi
