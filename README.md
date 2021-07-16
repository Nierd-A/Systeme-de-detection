# Systeme-de-detection
Projet de la formation développeur embarqué C++ par AJC.
Système de détection de présence et sonore grâce à une carte RaspberryPi 3 et un Arduino Nano.

## Description des documents
** led_controller **
Dossier contenant le programme à flasher sur la carte Arduino. Controller du capteur son et des leds.

** auto_log.sh **
Script shell d'enregistrement sur git du fichier log.txt sur la branche courante.

** log.txt **
Fichier de log de tous les événements survenus en cours de programme.

** main_controller.py **
Programme principal de lancement d'automatisation, d'écoute des capteurs et d'écriture des logs.

** robot_main_controller.robot **
Tests fonctionnels via RobotFramework. (A lancer hors RPi)

** setup_auto_log.sh **
Setup de la crontab pour pouvoir automatiser l'enregistrement des logs.

** test_main_controller.py **
Tests unitaires du programme principal.
