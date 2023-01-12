echo. > results.txt
echo 1. Неверные входные данные. Строк меньше нужного >> results.txt
18_Korshunov.exe < test01.txt >> results.txt

echo. >> results.txt
echo 2. Неверные входные данные. Строк больше нужного >> results.txt
18_Korshunov.exe < test02.txt >> results.txt

echo. >> results.txt
echo 3. Искомой функции нет в тексте программы >> results.txt
18_Korshunov.exe < test03.txt >> results.txt

echo. >> results.txt
echo 4. Искомая функция есть в тексте программы  >> results.txt
18_Korshunov.exe < test04.txt >> results.txt

echo. >> results.txt
echo 5. Искомая функция закомментирована  >> results.txt
18_Korshunov.exe < test05.txt >> results.txt

echo. >> results.txt
echo 6. Имеется прототип и вызов искомой функции перед определением.  >> results.txt
18_Korshunov.exe < test06.txt >> results.txt

echo. >> results.txt
echo 7. Вызов функции похож на определение  >> results.txt
18_Korshunov.exe < test07.txt >> results.txt

echo. >> results.txt
echo 8. Имя функции использовано как имя переменной >> results.txt
18_Korshunov.exe < test08.txt >> results.txt

echo. >> results.txt
echo 9. Тело искомой функции состоит из пустых строк  >> results.txt
18_Korshunov.exe < test09.txt >> results.txt

echo. >> results.txt
echo 10. Тело искомой функции состоит из строк с белыми разделителями >> results.txt
18_Korshunov.exe < test10.txt >> results.txt

echo. >> results.txt
echo 11. Тело искомой функции пустое >> results.txt
18_Korshunov.exe < test11.txt >> results.txt

echo. >> results.txt
echo 12. Тело функции состоит из комментариев  >> results.txt
18_Korshunov.exe < test12.txt >> results.txt

echo. >> results.txt
echo 13. Тело функции состоит из комментариев, пустых и непустых строк  >> results.txt
18_Korshunov.exe < test13.txt >> results.txt

echo. >> results.txt
echo 14. После заголовка определения искомой функции идут комментарии до тела >> results.txt
18_Korshunov.exe < test14.txt >> results.txt

echo. >> results.txt
echo 15. Вместо пробелов используются табы в заголовке функции >> results.txt
18_Korshunov.exe < test15.txt >> results.txt