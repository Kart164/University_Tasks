extrn ExitProcess: proc,  ;использование функций WinApi
      MessageBoxA: proc,
      GetUserNameA: proc,
      GetComputerNameA: proc,
      GetTempPathA: proc,
      GetVersionExA: proc,
      wsprintfA: proc
.data
cap db 'Task7', 0
fmt db 'Username: %s',0Ah,
       'Computer name: %s', 0Ah,
       'TMP Path: %s', 0Ah,
       'OS version: %d.%d.%d', 0
.code
szUNLEN equ 257
szMAX_COMP_NAME equ 16
szMAX_PATH equ 261

OSVERSIONINFO struct
    dwOSVersionInfoSize dword ?
    dwMajorVersion      dword ?
    dwMinorVersion      dword ?
    dwBuildNumber       dword ?
    dwPlatformId        dword ?
    szCSDVersion        db 128 dup(?)
OSVERSIONINFO ends



Start proc
local _msg[1024]                 :byte,
      _username[szUNLEN]         :byte,
      _compname[szMAX_COMP_NAME] :byte,
      _temppath[szMAX_PATH]      :byte,
      _v                         :OSVERSIONINFO,
      _size                      :dword
  sub RSP, 8*5
  and SPL, 0F0h

  mov _size, szUNLEN
  lea RCX, _username
  lea RDX, _size
  call GetUserNameA


  mov _size, szMAX_COMP_NAME
  lea RCX, _compname
  lea RDX, _size
  call GetComputerNameA

  mov _size, szMAX_PATH
  lea RCX, _size
  lea RDX, _temppath
  call GetTempPathA

  mov AL,0
  mov RCX, size _v
  lea RDI, _v
  rep stos byte ptr [RDI]
  mov _v.dwOSVersionInfoSize, size _v
  lea RCX, _v
  call GetVersionExA

  lea RCX, _msg
  lea RDX, fmt
  lea R8, _username
  lea R9,_compname
  lea RBX, _temppath
  mov 32[rsp], rbx ;Здесь и ниже, до вызова, компануется версия ОС
  lea RBX, _v.dwMajorVersion
  mov 24[rsp], rbx
  lea RBX, _v.dwMinorVersion
  mov 16[rsp], rbx
  lea RBX, _v.dwBuildNumber 
  mov 8[rsp], rbx
  call wsprintfA
  xor RCX, RCX
  mov R9, R9
  lea RDX, _msg
  lea R8, cap
  call MessageBoxA
  xor RCX, RCX
  call ExitProcess
Start endp
end