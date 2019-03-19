:- op(200, yfx, ~).
:- op(200, yfx, '..').

% rozvin(+StrucnySeznam,-UplnySeznam) 
rozvin([], []).
rozvin([X~Y..Z|Xs], [Res|Zbytek]) :- rozvinIntervalove(X, Y, Z, Res), rozvin([Xs], Zbytek).
rozvin([X..Y|Xs], [Res|Zbytek]) :- X < Y, doplnRostouciPosloupnost(1, X, Y, Res), rozvin([Xs], Zbytek);
                                   X > Y, doplnKlesajiciPosloupnost(1, X, Y, Res), rozvin([Xs], Zbytek).
rozvin([X|Xs], [X|Zbytek]) :- rozvin([Xs], Zbytek).

rozvinIntervalove(X, Y, Z, Res) :- X < Z, Kvocient is abs(X-Y), doplnRostouciPosloupnost(Kvocient, X, Z, [], Res);
                                   X > Z, Kvocient is abs(X-Y), doplnKlesajiciPosloupnost(Kvocient, X, Z, [], Res).

doplnRostouciPosloupnost(Kvocient, X, Z, Akum, Res) :- Y is X + Kvocient, Y =< Z, 
doplnRostouciPosloupnost(Kvocient, X, Z, Akum, Res). %doplnit