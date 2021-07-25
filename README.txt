Numele proiectului"Randemic" provine din 2 cuvinte : Random si Pandemic, acesta fiind o aplicatie ce simuleaza o pandemie pe un numar ales de persoane sau de orase. Ele cat si efectele pandemiei sunt generate aleatoriu impreuna cu caracteristicile lor de catre subprograme ce se intrepatrund, creeand miscari, infectari si profile realiste pentru Npc-uri si orase. 
La intrarea in program utilizatorul poate seta parametrii pentru virus, cat si densitatea populatiei sau numarul de orase. In timpul simularii sunt actualizate si afisate in timp real toate caracteristicile cat si statisticile globale. Starea de sanatate este marcata de o culoare, iar prin click se pot vedea toate caracteristicile individuale. 
Exista si posibilitatea ca o baza de date sa fie incarcata de utilizator, aceasta oferind posibilitatea analizei detaliate al unui scenariu predefinit (de exemplu evolutia infectarii a 2 orase care deja au inregistrat infectari).
Formulele legate de transmiterea virusului au fost bazate pe aceste 2 articole :
https://calculate.org.au/wp-content/uploads/sites/15/2018/10/spread-of-disease.pdf
https://www.ncbi.nlm.nih.gov/pmc/articles/PMC2359860/

Link-uri download (nu mai sunt updatate): 

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


 Cea mai mare parte din program a fost realizata in C++ utilizand Visual Studio, adica partea algoritmica: generarea Npc-urilor sau oraselor, prin functiile de randomizare si modurile prin care interactioneaza virusul cu persoanele.
Generarea de Npc-uri am optimizat-o prin crearea unei baze de date locala atat pentru atribute ce puteau fi luate de acestea(ex. prenume), cat si pentru stocarea fiecarei entitati generate. 
Scrierea si accesarea pentru baza de date a fost posibila datorita fisierelor JSON si notatiilor de acest tip, lucru ce a permis un workflow rapid, usor de editat, intre Excel, fisiere XML si JSON. 
Fiecare NPC si fiecare oras sunt considerate de cate JSON si C++ ca fiind obiecte separate ce prezinta diferite caracteristici: nume, sex, varsta, inaltime, starea de sanatate ,pozitia si gradul de sociabilitate, in cazul NPC-urilor , iar in cazul oraselor: numele, populatia si pozitia; toate contribuind la comportamentul individual si posibilitatea de transmitere a bolii.  Accesarea si manipularea pentru baza de date a fost realizata cu ajutorul librariei Jsoncpp utilizand parser-ul integrat si functiile adiacente.
Grafica a fost realizata utilizand SFML/OpenGL, simularea ruleaza in 60fps, fiind posibila schimbarea imaginii in modul fullscreen, optiunea de a reseta simularea direct din window cat si cea de a pune pauza.
Librariile SFML/OpenGL si Jsoncpp au fost incluse in proiect dupa ce au fost compilate si instalate utilizand CMake si fisiere amalgamte in Python shell.

Fundalul aplicatiei a fost desenat in Aseprite.

Cerinte de sistem:
Windows 7/8/10
Procesor dual-core
1GB RAM
3GB Stocare
Visual Studio(recomandat)/Code::Blocks
