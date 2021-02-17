extrn GetVersionExA: proc, ;Получение версии ОС
	  GetComputerNameA: proc, ;Получение имени компьютера
	  GetTempPathA: proc, ;Получение полного пути до папки Temp
	  GetUserNameA: proc ;Получение имени пользователя

;форматирование и системные функции

extrn wsprintfA: proc, ;Форматирование строки
	  MessageBoxA :proc, ;вызов объекта типа MessageBox
	  ExitProcess :proc ;функция с 4ch

.data
cap db 'Информация о компьютере', 0 ;Строка заголовка
fmt db 'Имя пользователя: %s',10, ;Строка выводимого сообщения
'Имя компьютера: %s', 10,
'Путь к папке Temp: %s', 10,
'Версия ОС: %d.%d.%d', 0
.code
;Длины строк, передаваемых в WinAIP
Size_Name_Comp equ 16
Size_User_Name equ 257
Size_Path equ 261
;описание структуры, хранящей информацию о версии ОС
OSVERSIONINFO struct
dwOSVersionInfoSize dd ?
dwMajorVersion dd ?
dwMinorVersion dd ?
dwBuildNumber dd ?
dwPlatformId dd ?
szCSDVersion db 128 dup(?)
OSVERSIONINFO ends

Start proc

;блок локальных переменных

;необходим для хранения результатов вызова WinAPI

;//----------------------------------------------------//

;финальная строка

local _msg[1024] :byte ;строки и структура для результата

local _username[Size_User_Name] :byte,
		_compname[Size_Name_Comp] :byte,
		_temppath[Size_Path] :byte,
		_v :OSVERSIONINFO

;буфер для хранения размера

local _size :dword
;выравниваем стек
sub RSP, 40
and SPL, 240
mov RCX, size _v ;Получение версии ОС
lea RDI, _v
rep stos byte ptr [RDI] ;stos для всех полей
mov _v.dwOSVersionInfoSize, size _v ;устанавливаем размер структуры и помещаем его в одно из полей структуры
lea RCX, _v
call GetVersionExA
;Получение имени компьютера
mov _size, Size_Name_Comp
lea RCX, _compname
lea RDX, _size
call GetComputerNameA
;Получение полного пути к папке Temp
mov _size, Size_Path
lea RCX, _size
lea RDX, _temppath
call GetTempPathA
mov _size, Size_User_Name
lea RCX, _username
lea RDX, _size
call GetUserNameA
lea RCX, _msg ;результирующая строка
lea RDX, fmt ;шаблон строки
lea R8, _username ;имя пользователя
lea R9, _compname ;имя компьютера
lea rbx, _temppath ;путь к папке temp
mov 32[rsp], rbx ;Здесь и ниже, до вызова, компануется версия ОС
lea RBX, _v.dwMajorVersion
mov 24[rsp], rbx
lea RBX, _v.dwMinorVersion
mov 16[rsp], rbx
lea RBX, _v.dwBuildNumber
mov 8[rsp], rbx
call wsprintfA
xor rcx, rcx
xor r9, r9
lea rdx, _msg ;текст сообщения
lea r8, cap ;текст для заголовка
call MessageBoxA
xor RCX, RCX
call ExitProcess
Start endp

End