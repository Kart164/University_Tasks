extrn GetVersionExA: proc, ;��������� ������ ��
	  GetComputerNameA: proc, ;��������� ����� ����������
	  GetTempPathA: proc, ;��������� ������� ���� �� ����� Temp
	  GetUserNameA: proc ;��������� ����� ������������

;�������������� � ��������� �������

extrn wsprintfA: proc, ;�������������� ������
	  MessageBoxA :proc, ;����� ������� ���� MessageBox
	  ExitProcess :proc ;������� � 4ch

.data
cap db '���������� � ����������', 0 ;������ ���������
fmt db '��� ������������: %s',10, ;������ ���������� ���������
'��� ����������: %s', 10,
'���� � ����� Temp: %s', 10,
'������ ��: %d.%d.%d', 0
.code
;����� �����, ������������ � WinAIP
Size_Name_Comp equ 16
Size_User_Name equ 257
Size_Path equ 261
;�������� ���������, �������� ���������� � ������ ��
OSVERSIONINFO struct
dwOSVersionInfoSize dd ?
dwMajorVersion dd ?
dwMinorVersion dd ?
dwBuildNumber dd ?
dwPlatformId dd ?
szCSDVersion db 128 dup(?)
OSVERSIONINFO ends

Start proc

;���� ��������� ����������

;��������� ��� �������� ����������� ������ WinAPI

;//----------------------------------------------------//

;��������� ������

local _msg[1024] :byte ;������ � ��������� ��� ����������

local _username[Size_User_Name] :byte,
		_compname[Size_Name_Comp] :byte,
		_temppath[Size_Path] :byte,
		_v :OSVERSIONINFO

;����� ��� �������� �������

local _size :dword
;����������� ����
sub RSP, 40
and SPL, 240
mov RCX, size _v ;��������� ������ ��
lea RDI, _v
rep stos byte ptr [RDI] ;stos ��� ���� �����
mov _v.dwOSVersionInfoSize, size _v ;������������� ������ ��������� � �������� ��� � ���� �� ����� ���������
lea RCX, _v
call GetVersionExA
;��������� ����� ����������
mov _size, Size_Name_Comp
lea RCX, _compname
lea RDX, _size
call GetComputerNameA
;��������� ������� ���� � ����� Temp
mov _size, Size_Path
lea RCX, _size
lea RDX, _temppath
call GetTempPathA
mov _size, Size_User_Name
lea RCX, _username
lea RDX, _size
call GetUserNameA
lea RCX, _msg ;�������������� ������
lea RDX, fmt ;������ ������
lea R8, _username ;��� ������������
lea R9, _compname ;��� ����������
lea rbx, _temppath ;���� � ����� temp
mov 32[rsp], rbx ;����� � ����, �� ������, ����������� ������ ��
lea RBX, _v.dwMajorVersion
mov 24[rsp], rbx
lea RBX, _v.dwMinorVersion
mov 16[rsp], rbx
lea RBX, _v.dwBuildNumber
mov 8[rsp], rbx
call wsprintfA
xor rcx, rcx
xor r9, r9
lea rdx, _msg ;����� ���������
lea r8, cap ;����� ��� ���������
call MessageBoxA
xor RCX, RCX
call ExitProcess
Start endp

End