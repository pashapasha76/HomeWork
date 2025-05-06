cities([1,2,3,4,5,6,7,8,9,10]).

% Город 1
distance(1,2,5).   distance(2,1,5).
distance(1,3,8).   distance(3,1,8).
distance(1,4,12).  distance(4,1,12).
distance(1,5,7).   distance(5,1,7).
distance(1,6,9).   distance(6,1,9).
distance(1,7,14).  distance(7,1,14).
distance(1,8,30).   distance(8,1,30).
distance(1,9,11).  distance(9,1,11).
distance(1,10,6).  distance(10,1,6).

% Город 2
distance(2,3,9).   distance(3,2,9).
distance(2,4,4).   distance(4,2,4).
distance(2,5,15).  distance(5,2,15).
distance(2,6,2).   distance(6,2,2).
distance(2,7,7).   distance(7,2,7).
distance(2,8,10).  distance(8,2,10).
distance(2,9,13).  distance(9,2,13).
distance(2,10,1).  distance(10,2,1).

% Город 3
distance(3,4,6).   distance(4,3,6).
distance(3,5,3).   distance(5,3,3).
distance(3,6,11).  distance(6,3,11).
distance(3,7,8).   distance(7,3,8).
distance(3,8,5).   distance(8,3,5).
distance(3,9,4).   distance(9,3,4).
distance(3,10,7).  distance(10,3,7).

% Город 4
distance(4,5,10).  distance(5,4,10).
distance(4,6,7).   distance(6,4,7).
distance(4,7,9).   distance(7,4,9).
distance(4,8,8).   distance(8,4,8).
distance(4,9,12).  distance(9,4,12).
distance(4,10,2).  distance(10,4,2).

% Город 5
distance(5,6,4).   distance(6,5,4).
distance(5,7,6).   distance(7,5,6).
distance(5,8,11).  distance(8,5,11).
distance(5,9,5).   distance(9,5,5).
distance(5,10,9).  distance(10,5,9).

% Город 6
distance(6,7,3).   distance(7,6,3).
distance(6,8,7).   distance(8,6,7).
distance(6,9,10).  distance(9,6,10).
distance(6,10,8).  distance(10,6,8).

% Город 7
distance(7,8,12).  distance(8,7,12).
distance(7,9,15).  distance(9,7,15).
distance(7,10,4).  distance(10,7,4).

% Город 8
distance(8,9,6).   distance(9,8,6).
distance(8,10,7).  distance(10,8,7).

% Город 9
distance(9,10,5).  distance(10,9,5).

route_length(Route, Length) :-
    compute_length(Route, 0, Length).

compute_length([_], Length, Length). % Остановка, когда остался 1 город
compute_length([City1, City2 | Rest], Acc, Length) :-
    distance(City1, City2, D),
    NewAcc is Acc + D,
    compute_length([City2 | Rest], NewAcc, Length).

generate_route(First, Rest, Route) :-
    permutation(Rest, PermutedRest),
    Route = [First | PermutedRest].

find_shortest_route :-
    cities(Cities),
    Cities = [First | Rest],
    findall(Route, generate_route(First, Rest, Route), Routes),
    findall(Length-Route, (member(Route, Routes), route_length(Route, Length)), Pairs),
    keysort(Pairs, Sorted),
    Sorted = [MinLength-MinRoute | _],
    write('Shortest Route: '), write(MinRoute), nl,
    write('Length: '), write(MinLength), nl.

?- find_shortest_route.