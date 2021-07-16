*** Settings ***

Library                     Dialogs
Library                     Process

*** Test Cases ***

Test séquence capteur présence
    Execute Manual Step     Verifier le bon fonctionnement du capteur de présence
    
Test séquence capteur son
    Execute Manual Step     Verifier le bon fonctionnement du capteur de son / Clignotement led verte et rouge

Test séquence en attente
    Execute Manual Step     Verifier que le led sont en séquence chenillard

