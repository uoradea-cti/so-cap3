# Sisteme de Operare – Capitolul 3

**1.** Realizați un interpretor de comenzi propriu în următoarele condiții:
- recunoaște comenzile DIR, TIME, DATE, COMANDA, ECOU;
- orice altă comandă o consideră un program executabil, dat cu extensie (`*.com`, `*.exe`), și îl lansează în execuție. Dacă nu se specifică directorul în care se află programul, căutarea se face în directorul curent și apoi în cele din PATH (funcția spawnvp). Dacă lansarea nu reușește, se afișează „Comanda incorecta”;
- nu trebuie să recunoască redirectări, filtrări și nici să execute fișiere de comenzi indirecte;
- comenzile DIR, TIME, DATE vor fi transmise spre execuție la interpretorul de comenzi al sistemului (COMMAND.COM, azi cmd.exe);
- comanda COMANDA lansează interpretorul de comenzi al sistemului până se tastează EXIT;
- comanda ECOU este o comandă internă care afișează toate argumentele primite ca parametru;
- se consideră ca separator în cadrul liniei de comandă doar spațiul.

**2.** Îmbunătățiți interpretorul anterior pentru a permite recunoașterea `<`, `>` ca redirecționări ale intrării/ieșirii, realizând efectiv redirecționările.
