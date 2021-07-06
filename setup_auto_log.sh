#!/bin/bash

#WARNING : chemin du script en absolu ! 
#Evolution : choix de la frequence d'enregistrement par l'utilisateur
auto_cmd="*/1 * * * * bash /home/pi/Desktop/projet/Systeme-de-detection/auto_log.sh"

if [ $# -eq 0 ]
then
    #ajout de droit d execution du script auto_log.sh
    chmod u+x auto_log.sh

    #mise en place de la crontab
    (crontab -l 2>/dev/null; echo "$auto_cmd") | crontab -
fi

#suppression de l'action crontab ?
#WARNING : suppression totale de la crontab
#Evolution : supprimer uniquement la commande mise en place par ce script
if [[ $1 == "-r" ]]
then
    crontab -r
fi
