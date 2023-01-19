# :tickets: TicketMaster
Proiect final POO, anul 2

## :pushpin: Mod de rulare

### Utilizarea sistemului de baza

Pentru rularea ghidata se ruleaza:
```bash
TicketMaster.exe
```

Pentru verificarea biletelor dintr-un fisier se ruleaza:
```bash
TicketMaster.exe -f [numefisier.txt]
```

Pentru salvarea unui bilet in format PDF se adauga la comanda de mai sus `--pdf`:
```bash
TicketMaster.exe -f [numeFisier.txt] --pdf
```
Acestea vor fi salvate in directorul curent, sub forma `Bilet-[nrBiletValid].pdf`

*Pentru afisarea mesajelor de mai sus, se poate rula programul cu parametrul `-h` sau `--help`.*

### Utilizarea sistemului de generare PDF

Necesare:
* NodeJs
* PM2 (Pentru deployment)
* Nginx (Pentru reverse proxy)

Pentru rulare intr-un mediu de dezvoltare:
```bash
cd PDFMicroservice
npm install # instalare dependente
npm run start # rulare server Node
```

Pentru deployment pe un server se poate folosi PM2 impreuna cu Nginx reverse proxy:
```bash
pm2 start app.js
```

## :gear: Functionalitati
- Creare locatii cu:
  - Numar dinamic de zone
  - Zone cu o harta ce poate afisa statusul locului (disponibil/indisponibil/cumparat/checked in)
  - Posibilitatea reutilizarii unei locatii odata ce este adaugata in platforma
- Creare evenimente cu:
  - Preturi diferite in functie de zonele locatiei
  - Posibilitatea vizualizarii vanzarilor si a altor statistici
  - Cumpararea unui bilet direct din interfata (+generarea unui ID unic per bilet)
- Sistem de utilizatori cu:
  - Permisiuni (Admin/Base user)
  - Profil personal cu acces rapid la bilete
- Posibilitatea utilizarii din linia de comanda pentru verificarea ID-urilor biletelor
- Serviciu online pentru generare PDF in functie de nume eveniment, zona, rand si loc.

Cerintele proiectului se pot gasi la adresa [aceasta (Google Docs)](https://docs.google.com/document/u/1/d/e/2PACX-1vTg53nIXzeXTzidhduHXHXL5puY6mZ9IIU_YVnLcPDZfKTz67sOlrXGnjxOLsmjRDI9s9vdOaSVzjZF/pub).

### Documentatie API microservice PDF

#### `GET` `[endpoint]/generare-bilet`

Parametrii query **necesari** (lipsa lor va afisa un mesaj de eroare):

* `numeEveniment`: string ce contine numele evenimentului
* `zonaEveniment`: string ce contine numele zonei biletului
* `randEveniment`: string ce contine randul unde se va situa participantul
* `locEveniment`: string locul pe randul ales unde va sta participantul

Exemplu query (prin endpoint public disponibil):

```
http://api.ticketmaster.mihaisturza.ro/generare-bilet?numeEveniment=Eveniment&zonaEveniment=Zona&randEveniment=1&locEveniment=1
```

## :rotating_light: Probleme identificate si posibile optimizari
Cateva lucruri pe care le puteam face mai bine, dar nu le-am facut.

- Biletele sunt salvate pentru clienti sub forma ID-ului de bilet, lucru ce creste timpul de executie pe masura ce apar evenimente (`O(n*log(m))` pentru gasirea informatiilor unui singur bilet salvat in lista clientului)
- Readaugarea locatiilor in sistem este facuta prin compararea numelui locatiei + numele zonelor din lista tuturor locatiilor gasite in evenimente. Adaugarea unui ID ar scadea semnificativ timpul de cautare dar tot ar exista spatiu pentru mai bine.
- Meniul de utilizator este repetat, in 3 locuri, pentru fiecare situatie de permisiuni posibila. O rezolvare pe care doream sa o implementez consta intr-un vector de functii (prin pointeri) ce contineau functiile specifice pentru fiecare tip de utilizator - rezolvand problema repetarii care exista momentan.
