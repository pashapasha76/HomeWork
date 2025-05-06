allPoints :: [(Integer, Integer)]
allPoints = (0, 0) : loop 1
  where
    loop n = 
      [ (x, n)  | x <- [-n .. n] ]         
      ++ [ (n, y)  | y <- [n-1, n-2 .. -n] ]
      ++ [ (x, -n) | x <- [n-1, n-2 .. -n] ]
      ++ [ (-n, y) | y <- [-n+1 .. n-1] ]  
      ++ loop (n + 1)

