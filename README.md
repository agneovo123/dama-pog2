# dama-pog2
Dáma játék Prog. II-höz

## fordítás:
Visual Studio-val megnyitás után F5-ös gomb megnyomása

## futtatás:
Visual Studio-val megnyitás után F5-ös gomb megnyomása

## használat:
Lépéseket <<betű szám betű szám (kezdő és végpont) formátumban kell megadni pl.: <<b 3 a 4 (a '<<' nem kell, azt a program írja ki)

## példa input és elvárt eredmény
A program először megkérdezi, hogy kérünk-e leírást, erre vagy ">>1"-el, majd megint ">>1"-el válaszolunk, 
vagy ">>2"-vel a játék kezdéséhez
ezután pl ">>b 3 a 4" inputra
a b-3-ban lévő X az a-4-es mezőre ugrik.

## játék-leírás:

- O = világos
- @ = világos dáma
- X = sötét
- \# = sötét dáma

- Sötét kezd
- Ütéskényszer van (ütéssorozatot muszáj végrehajtani)
- Sima bábu csak előre léphet, egyesével, és lépésenként 1-et üthet
- Szemközti sor elérésekor a bábú dámává változik
- Dáma hátrafele is léphet és üthet is
- Dáma is csak egyet léphet, kivéve amikor üt
- Dáma nekifutásból, egybefüggőleg bármennyi elenséges bábut üthet, túlfuthat

A szabályokat a [wikipédiáról](https://hu.wikipedia.org/wiki/D%C3%A1maj%C3%A1t%C3%A9k) kukáztam össze

## hibák:
- csak 1 játékvége eset van: az egyik játékos összes bábuja ki lett ütve
- ütéskényszer szabályt hibásan értelmeztem, ennek az lett az eredménye, hogy nem csak ütés után jön létre az ütéskényszer
- ütéskényszer megszűnését nem ellenőrzöm, így ha azt nem szüntetjük meg, bármennyit léphetünk másik bábuval


GitHub link: https://github.com/agneovo123/dama-pog2