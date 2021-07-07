#Importation des librairies

import unittest
from main_controller import capteur_presence
from main_controller import capteur_son

#Classe de test permettant de valider les fonctions

class TestController(unittest.TestCase):
    
    def test_capteur_presence(self):
        self.assertNotEqual(capteur_presence(0, -1),-1)
        self.assertEqual(capteur_presence(1, -1),-1)
    
    def test_capteur_son(self):
        self.assertNotEqual(capteur_son(1, -1),-1)
        self.assertEqual(capteur_son(0, -1),-1)

if __name__ == '__main__':
    unittest.main()

