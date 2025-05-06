
                :- dynamic position/3.
                :- dynamic cluster/4.

                cluster(Type, X, Y, Size) :- 
                    findall((X1, Y1), position(Type, X1, Y1), Positions),
                    cluster_points(Positions, [], Clusters, 5.0, 3),
                    member((X, Y, Size), Clusters).

                cluster_points([], Clusters, Clusters, _, _).

                cluster_points([(X,Y)|Ps], Acc, Clusters, Radius, MinSize) :- 
                    (member((CX, CY, CSize), Acc),
                        distance((X,Y), (CX,CY), D),
                        D =< Radius
                    ->  
                        NewSize is CSize + 1,
                        NewCX is (CX * CSize + X) / NewSize,
                        NewCY is (CY * CSize + Y) / NewSize,
                        select((CX, CY, CSize), Acc, TempAcc),
                        NewAcc = [(NewCX, NewCY, NewSize) | TempAcc]
                    ;   
                        NewAcc = [(X, Y, 1) | Acc]
                    ),
                    cluster_points(Ps, NewAcc, Clusters, Radius, MinSize).

                distance((X1, Y1), (X2, Y2), D) :- 
                    DX is X1 - X2,
                    DY is Y1 - Y2,
                    D is sqrt(DX*DX + DY*DY).
            