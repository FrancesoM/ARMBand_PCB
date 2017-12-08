SET PATH=C:\Keil_v5\ARM\ARMCC\Bin;C:\Program Files (x86)\Intel\iCLS Client\;C:\ProgramData\Oracle\Java\javapath;C:\Program Files\Intel\iCLS Client\;C:\windows\system32;C:\windows;C:\windows\System32\Wbem;C:\windows\System32\WindowsPowerShell\v1.0\;C:\Program Files (x86)\CodeBlocks\MinGW\bin;C:\Program Files (x86)\Arduino\hardware\tools\avr\bin;C:\Program Files\MATLAB\MATLAB Runtime\v901\runtime\win64;C:\Program Files (x86)\Microchip\xc16\v1.32\bin;C:\Program Files (x86)\Microchip\xc8\v1.43\bin;C:\Users\Francesco\Desktop\GNU-Toolchain\bin;C:\Program Files\Intel\WiFi\bin\;C:\Program Files\Common Files\Intel\WirelessCommon\;C:\Program Files (x86)\Microchip\xc8\v1.44\bin;C:\Program Files (x86)\Microchip\xc16\v1.33\bin;C:\Program Files (x86)\Intel\Intel(R) Management Engine Components\DAL;C:\Program Files\Intel\Intel(R) Management Engine Components\DAL;C:\Program Files (x86)\Intel\Intel(R) Management Engine Components\IPT;C:\Program Files\Intel\Intel(R) Management Engine Components\IPT;C:\Users\Francesco\Anaconda3;C:\Users\Francesco\Anaconda3\Scripts;C:\Users\Francesco\Anaconda3\Library\bin;C:\Users\Francesco\AppData\Local\Microsoft\WindowsApps;C:\Program Files (x86)\Notepad++
SET CPU_TYPE=STM32F413ZHTx
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=i2cfmp_nucleo
SET CPU_CLOCK=0x05F5E100
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\i2cfmp_nucleo\stm32f4xx_hal_cortex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\i2cfmp_nucleo\stm32f4xx_hal_flash_ramfunc.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\i2cfmp_nucleo\stm32f4xx_hal_dma_ex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\i2cfmp_nucleo\stm32f4xx_hal_gpio.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\i2cfmp_nucleo\stm32f4xx_hal_pwr.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\i2cfmp_nucleo\stm32f4xx_hal.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\i2cfmp_nucleo\stm32f4xx_hal_tim_ex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\i2cfmp_nucleo\stm32f4xx_hal_rcc.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\i2cfmp_nucleo\stm32f4xx_hal_rcc_ex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\i2cfmp_nucleo\stm32f4xx_hal_dma.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\i2cfmp_nucleo\stm32f4xx_hal_flash_ex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\i2cfmp_nucleo\stm32f4xx_hal_flash.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\i2cfmp_nucleo\stm32f4xx_hal_fmpi2c_ex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\i2cfmp_nucleo\stm32f4xx_hal_uart.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\i2cfmp_nucleo\stm32f4xx_hal_tim.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\i2cfmp_nucleo\stm32f4xx_hal_fmpi2c.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\i2cfmp_nucleo\stm32f4xx_hal_pwr_ex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\i2cfmp_nucleo\stm32f4xx_hal_msp.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\i2cfmp_nucleo\main.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\i2cfmp_nucleo\stm32f4xx_it.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\i2cfmp_nucleo\system_stm32f4xx.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmAsm" --Via ".\i2cfmp_nucleo\startup_stm32f413xx._ia"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmLink" --Via ".\i2cfmp_nucleo\i2cfmp_nucleo.lnp"
"C:\Keil_v5\ARM\ARMCC\Bin\fromelf.exe" ".\i2cfmp_nucleo\i2cfmp_nucleo.axf" --i32combined --output ".\i2cfmp_nucleo\i2cfmp_nucleo.hex"
