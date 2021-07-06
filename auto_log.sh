#!/bin/bash

#WARNING : PATH du dossier git en absolu !
git_path="/home/pi/Desktop/projet/Systeme-de-detection"
#deplacement dans le dossier git
cd $git_path

#test presence du fichier
if [ ! -f log.txt ]
then 
    exit 0 #rien a faire 
fi

#commit des logs uniquement sans affichage
git add log.txt
git commit -m "LOG AUTO COMMIT - $(date '+%Y-%m-%d %H:%M:%S') " log.txt >/dev/null


#push des logs sans affichage
git push >/dev/null

