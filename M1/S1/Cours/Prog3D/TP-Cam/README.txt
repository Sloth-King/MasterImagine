TP - Caméra 
MANSOUR Andrew 
22110677

Je n'étais pas certain s'il fallait un rapport ou un readme comme celui-ci, je m'éxcuse si un rapport était attendu.

Voici le résumé des fonctionnalités implémentées : 

II - IMGUI : toutes les questions ont été faites

III - Côntrole de la caméra : Les parties 1 , 2 et 3 sont faites mais pas la partie optionnelle par manque de temps. 
Pour les deux modes, j'ai ajouté le mouvement avec right (pour q et d) pour rendre le le mouvement plus agréable.
Les défauts seraient la sensibilité et la vitesse de base des mouvements et de la rotation. J'ai eu du mal a trouver une bonne vitesse.

IV - Les Helpers : les 3 helpers sont implémentés.

V - Côntrole affiné de la rotation : Le clip du yaw et le clamp du pitch sont implémentés.

VI - Transition : La transition à la position de départ est faite après l'appui du bouton reset. 
J'ai eu beaucoup de difficultés à comprendre comment gérer le temps car on a pas l'habitude de coder en temps réel.
Au moins, on ne manipule pas souvent les méthodes qui font le "update" en temps réel, donc c'était difficile mais très interessant a gérer.

VII - Camera Third : L'affichage du target fonctionne, il peut se deplacer avec zqsd et espace. 
La caméra s'attache au personnage avec un bouton IMGUI, mais la rotation qu'il fait semble être du roll et non pas la rotation yaw désirée.
Je n'ai pas réussi à régler celà. Mes autres tentatives sont commentées dans la méthode.
(Le code pour cette partie se trouve dans TP.cpp et non pas Camera.cpp)