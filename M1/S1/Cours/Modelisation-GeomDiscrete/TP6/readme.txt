NOM Prénom : MANSOUR Andrew 
Numéro étudiant : 22110677


Utilisation : 
“K” pour sauvegarder une keyframe
“S” pour sauvegarder une animation
“P” pour jouer l’animation
“R” pour reset le squelette et les keys et animations


Un exemple d’ainmation se trouve dans le dossier nommé “walkAnim.webm”


Fonctionnalités implémentées : 


-Déplacement snake-like : Pour effectuer ce mouvement fluide, on définit deux méthodes, initMove et recursiveMove. InitMove fait le mouvement du nœud sélectionné puis appel recursiveMove pour gérer les mouvements des nœuds suivants. RecursiveMove calcule la distance entre le noeud et tous ses noeuds suivants, si cette distance est supérieure à la taille initiale de l'arête initiale, cela signifie qu’il y a trop d’espace entre les deux noeuds à cause du déplacement, et qui va donc ramener le noeud suivant plus proche au noeud actuel, et se faire sur tous les noeuds qui suivent.


-Déplacement rigide : Comme pour le déplacement snake-like, on dispose de deux méthodes initMove et recursiveMove, initMove est identique a la précédente. Ici recursiveMove ne va pas comparer de distances ni de taille d'arêtes et va simplement déplacer le reste des nœuds suivants de la même manière que le nœud sélectionné, ce qui va conserver les angles et les distances par défaut.


-Système d’animation : Le système d’animation est divisé en plusieurs méthodes afin de fonctionner. Tout d’abord, le code de animation.js est utilisé pour jouer l’animation. Pour sauvegarder un keyframe, on appuie sur la touche K, qui va appeler la méthode saveKey du displayer, qui elle va appeler saveKeyframe du squelette. Cette méthode va copier les valeurs cc du node , ainsi que valeurs to et from des arêtes, et les ajoutés à une liste nommée keys (qui est attribut du squelette). 
Ensuite, quand on clique sur S, on peut sauvegarder une animation. saveAnimation va appeler initAnim, qui va commencer à interpoler les frames entre chaque keyframe. interpolateFrames prend en paramètre deux key, et calcul les frames entre ces deux. Le nombre de frames a interpoler (nombre de frames / nombre de keyframe - 1) est calculé, puis les valeurs cc de ces frames sont interpolées linéairement. Après avoir effectué ces calculs, les keyframes et toutes les frames entre chacune des keys sont ajoutés à une liste, qui va être copiée dans savedFrames qui est un attribut de la classe squelette. 
Enfin, pour mettre à jour l’animation, la méthode updateSkeleton est appelée qui prend en paramètre un frame, et qui va remplacer les valeurs des nœuds et arêtes du squelette par ceux du frame donné.


Fonctionnalités non implémentées : 


rotation/AngleMove : Malgré beaucoup de tentatives, je n’ai pas réussi à coder cette fonction avant les délais, la situation qui est le plus souvent apparue est que les nœuds allaient directement au coin en haut à gauche de la page au moindre déplacement de la roue de la souris.


Difficultés : 

L’animation du personnage a été assez longue sans l’implémentation de la rotation, donc souvent quand le personnage devait bouger, les distances entre des noeuds changeaient involontairement