SET PATH=D:\Keil_v5\ARM\ARMCLANG\Bin;C:\Program Files (x86)\NVIDIA Corporation\PhysX\Common;C:\Program Files\Java\jdk1.8.0_152\bin;C:\Program Files (x86)\Common Files\Oracle\Java\javapath;C:\Program Files (x86)\Common Files\NetSarang;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;D:\Program Files\MATLAB\R2016b\runtime\win64;D:\Program Files\MATLAB\R2016b\bin;D:\Program Files\MATLAB\R2016b\polyspace\bin;D:\Program Files (x86)\NetSarang\Xshell 7\;C:\Program Files (x86)\Windows Kits\8.1\Windows Performance Toolkit\;C:\ProgramData\chocolatey\bin;D:\Program Files\nodejs\;C:\Program Files\Git\cmd;E:\cmder;D:\Users\xiaofei\AppData\Local\Programs\Python\Python39\;E:\arm_stm32\OpenOCD-20210301-0.10.0\bin;E:\arm_stm32\make;D:\Program Files (x86)\GNU Tools ARM Embedded\5.4 2016q3\bin;D:\mingw64\bin;C:\cmake-3.21.3-windows-x86_64\bin;E:\Xilinx\Vivado\2018.3\bin;D:\Program Files (x86)\IVI Foundation\VISA\WinNT\Bin\;C:\Program Files\IVI Foundation\VISA\Win64\Bin\;D:\Program Files (x86)\IVI Foundation\VISA\WinNT\Bin;C:\Program Files\dotnet\;C:\Program Files\Microsoft SQL Server\130\Tools\Binn\;C:\Users\xiaofei\AppData\Local\Programs\Python\Python39\Scripts\;C:\Users\xiaofei\AppData\Local\Programs\Python\Python39\;C:\Users\xiaofei\AppData\Local\Programs\Python\Python37\Scripts\;C:\Users\xiaofei\AppData\Local\Programs\Python\Python37\;D:\Users\xiaofei\AppData\Local\Programs\Python\Python38\;C:\Users\xiaofei\AppData\Local\Microsoft\WindowsApps;D:\Program Files\Bandizip\;C:\Users\xiaofei\AppData\Local\Programs\Microsoft VS Code\bin;D:\x86_64-8.1.0-release-posix-seh-rt_v6-rev0\mingw64\bin;C:\Users\xiaofei\AppData\Roaming\npm;E:\cmder;D:\Users\xiaofei\AppData\Local\Programs\Python\Python38\Scripts;C:\Qt\Qt5.9.0\Tools\mingw530_32\bin;D:\Program Files (x86)\GNU Tools ARM Embedded\5.4 2016q3\bin;E:\arm_stm32\make;E:\arm_stm32\OpenOCD-20210301-0.10.0\bin;D:\mingw64\bin;C:\cmake-3.21.3-windows-x86_64\bin;;D:\Program Files\JetBrains\PyCharm 2021.3\bin;;C:\Users\xiaofei\.dotnet\tools;C:\Users\xiaofei\AppData\Local\Programs\EmEditor
SET CPU_TYPE=STM32F401CCUx
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=demo
SET CPU_CLOCK=0x017D7840
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmAsm" --Via "demo\startup_stm32f401xc._ia"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"demo\lcd.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"demo\lcd_init.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"demo\main.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"demo\gpio.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"demo\dma.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"demo\rtc.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"demo\spi.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"demo\tim.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"demo\stm32f4xx_it.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"demo\stm32f4xx_hal_msp.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"demo\stm32f4xx_hal_pcd.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmLink" --Via "demo\demo.lnp"
"D:\Keil_v5\ARM\ARMCLANG\Bin\fromelf.exe" "demo\demo.axf" --i32combined --output "demo\demo.hex"
