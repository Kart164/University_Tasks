extrn ExitProcess :proc,  ;использование функций WinApi
      MessageBoxA :proc

.data
caption db 'My Name', 0   ;заголовок
message db 'Kartashov Fedor 221',  0 ;текст окна

.code
Start proc
  sub RSP, 8*5 ;выравнивание стека по _fastcall
  ;подготовка данных для передачи в massagebox
  xor RCX, RCX ;номер окна = 0  (вывод поверх рабочего стола)
  lea RDX, message ;передача адресов строк
  lea R8, caption
  xor R9, R9 ;передаем тип окна

  call MessageBoxA

  xor RCX, RCX ;код завершения проги

  call ExitProcess
Start endp
end