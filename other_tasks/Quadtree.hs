data Point = Point {x :: Double, y :: Double} deriving (Show)

data QuadTree = Leaf Double Double Double Double [Point]
             | Node Double Double Double Double QuadTree QuadTree QuadTree QuadTree
             deriving (Show)

newLeaf :: Double -> Double -> Double -> Double -> QuadTree
newLeaf x y w h = Leaf x y w h []

insert :: Point -> QuadTree -> QuadTree
insert p (Leaf lx ly lw lh ps)
  | length ps < 4 = Leaf lx ly lw lh (p:ps)
  | otherwise =
      let halfW = lw/2
          halfH = lh/2
          nw = newLeaf lx ly halfW halfH
          ne = newLeaf (lx + halfW) ly halfW halfH
          sw = newLeaf lx (ly + halfH) halfW halfH
          se = newLeaf (lx + halfW) (ly + halfH) halfW halfH
          node = Node lx ly lw lh nw ne sw se
      in foldl (flip insert) node (p:ps)

insert p (Node nodeX nodeY nodeW nodeH nw ne sw se) = 
  let px = x p
      py = y p
      halfW = nodeW / 2
      halfH = nodeH / 2
  in if px < nodeX + halfW && py < nodeY + halfH 
     then Node nodeX nodeY nodeW nodeH (insert p nw) ne sw se
     else if px >= nodeX + halfW && py < nodeY + halfH 
          then Node nodeX nodeY nodeW nodeH nw (insert p ne) sw se
          else if px < nodeX + halfW && py >= nodeY + halfH 
               then Node nodeX nodeY nodeW nodeH nw ne (insert p sw) se
               else Node nodeX nodeY nodeW nodeH nw ne sw (insert p se)

search :: Point -> Double -> QuadTree -> [Point]
search (Point cx cy) radius (Leaf lx ly lw lh ps) = 
  filter (\(Point px py) -> (px - cx)^2 + (py - cy)^2 <= radius^2) ps

search center@(Point cx cy) radius (Node nodeX nodeY nodeW nodeH nw ne sw se) =
  if intersect (Point cx cy) radius (nodeX, nodeY, nodeW, nodeH)
  then concatMap (search center radius) [nw, ne, sw, se]
  else []
  where
    intersect :: Point -> Double -> (Double, Double, Double, Double) -> Bool
    intersect (Point cx cy) r (x, y, w, h) =
      let closestX = max x (min (x + w) cx)
          closestY = max y (min (y + h) cy)
          dx = cx - closestX
          dy = cy - closestY
      in dx*dx + dy*dy <= r*r

main :: IO ()
main = do
  let tree = foldl (flip insert) (newLeaf 0 0 100 100)
        [Point 10 10, Point 20 20, Point 30 30, Point 40 40, Point 15 15]
      
      result = search (Point 15 15) 10 tree

  print result