Le repertoire interface contient la definition de ce qui est visible de l'exterieur
du composant 0.

Lors de la publication vous mettez ce que vous decidez de publier dans le
repertoire "publication" et vous commitez le contenu dans github.
A chaque publication, la version doit etre differente.
A chaque publication, mettez un message sur le forum pour que les autres groupes en soient notifies.

Le repertoire publication contient:

- interfaces 
	un seul fichier .h
	un fichier .lib pour le linker

- Debug et/ou Release
	un fichier .dll    (le composant executable)
	un fichier .pdb    (les informations de debug, disponibles meme en mode release)



