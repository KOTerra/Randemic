

Descriere:
 Numele proiectului"Randemic" provine din 2 cuvinte : Random si Pandemic, acesta fiind o aplicatie ce simuleaza o pandemie pe un numar ales de persoane,acestea
 din urma cat si efectele pandemiei fiind generate aleatoriu impreuna cu caracteristicile lor de catre subprograme ce se intrepatrund creeand miscari, infectari si profile realiste pentru Npc-urile generate. 
La intrarea in program utilizatorul poate seta parametrii pentru virus, cat si densitatea populatiei generata. In timpul simularii sunt actualizate si afisate in timp real toate caracteristicile Npc-urilor cat si statisticile globale. Starea de sanatate a fiecarui Npc este marcata de o culoare, iar prin click se pot vedea toate caracteristicile acestuia. 
Formulele legate de transmiterea virusului au fost bazate pe aceste 2 articole :
https://calculate.org.au/wp-content/uploads/sites/15/2018/10/spread-of-disease.pdf
https://www.ncbi.nlm.nih.gov/pmc/articles/PMC2359860/

Link-uri download (recomandam Mega): 

https://mega.nz/folder/5O4jBQ5Q#yHpGt8fTidU9gSD-KaO7Xw
https://github.com/Mars-Zero/Randemic
https://drive.google.com/drive/folders/163EIUlh73lo3H6reYmOrmONBpemIuQ7v?usp=sharing


Tehnologii:

C++
SFML/OpenGL
JSON
Excel/XML
Python shell 3.8
CMake

 Cea mai mare parte din program a fost realizata in C++ utilizand Visual Studio, adica partea algoritmica: generarea Npc-urilor prin functiile de randomizare si modurile prin care interactioneaza virusul cu persoanele si acestea din urma intre ele. 
Generarea de Npc-uri am optimizat-o prin crearea unei baze de date locala atat pentru atribute ce puteau fi luate de acestea(ex. prenume), cat si pentru stocarea fiecarei entitati generate. 
Scrierea si accesarea pentru baza de date a fost posibila datorita fisierelor JSON si notatiilor de acest tip, lucru ce a permis un workflow rapid, usor de editat, intre Excel, fisiere de tip XML si JSON. 
Fiecare Npc-uri este considerat de cate JSON si C++ un obiect separat ce prezinta urmatoarele caracteristici: nume,sex,varsta,inaltime si gradul de sociabilitate, toate contribuind la comportamentul individual si posibilitatea de a fi infectat de alt Npc. 
accesarea si manipularea pentru baza de date a fost realizata cu ajutorul librariei Jsoncpp utilizand parser-ul integrat si functiile adiacente.   
Grafica a fost realizata utilizand SFML/OpenGL, simularea ruleaza in 60fps, fiind poisbila schimbarea imaginii in modul fullscreen, optiunea de a reseta simularea direct din window cat si cea de a pune pauza cand focusul nu mai este pe window.
Librariile SFML/OpenGL si Jsoncpp au fost incluse in proiect dupa ce au fost compilate si instalate utilizand CMake si fisiere amalgamte in Python shell.  
Fundalul aplicatiei a fost desenat in Aseprite.


Cerinte sistem:
Windows 7/8/10
Procesor dual-core
100MB RAM
1GB Stocare
Visual Studio(recomandat)/Code::Blocks

