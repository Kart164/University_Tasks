extrn ExitProcess :proc,  ;������������� ������� WinApi
      MessageBoxA :proc

.data
caption db 'My Name', 0   ;���������
message db 'Kartashov Fedor 221',  0 ;����� ����

.code
Start proc
  sub RSP, 8*5 ;������������ ����� �� _fastcall
  ;���������� ������ ��� �������� � massagebox
  xor RCX, RCX ;����� ���� = 0  (����� ������ �������� �����)
  lea RDX, message ;�������� ������� �����
  lea R8, caption
  xor R9, R9 ;�������� ��� ����

  call MessageBoxA

  xor RCX, RCX ;��� ���������� �����

  call ExitProcess
Start endp
end