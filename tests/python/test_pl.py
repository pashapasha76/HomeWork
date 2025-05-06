from pyswip import Prolog
prolog = Prolog()
prolog.assertz("father(michael,john)")
print(list(prolog.query("father(X,Y)")))