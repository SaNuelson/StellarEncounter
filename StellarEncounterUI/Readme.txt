Project created solely to create basic GUI implementation, should be added to the SEGB, where work will continue.
Or I'll just create another project, easy as that.

Momentálne UIElements fungujú pomocou function pointerov, ktoré ale asi nebudú stačiť na neskoršie implementácie. Takto by bolo treba na každý button samostatnú globálnu funkciu,
ktorá by jednoducho otočila nejaký bool, ktorý by pri loope v scéne zavolal danú funkcionalitu, ale to je ako motykou do stromu. Skôr či neskôr asi prídu na rad eventy.
Ešte pri buttonoch by to nikoho tak nebolelo, ale ak by som chcel napr. naimplementovať EnergyFocusTriangle, nemám šancu... mám, dalo by sa, cez parametre. Ale zbytočne, na to
presne sú eventy.