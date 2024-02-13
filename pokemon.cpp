#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()

using namespace std;

// Déclaration préalable des classes
class Pokemon;
class Dresseur;

// Classe représentant un Pokémon
class Pokemon {
private:
    string nom;
    int niveau;
    int pointsDeVie;
public:
    Pokemon(string n, int lvl) : nom(n), niveau(lvl), pointsDeVie(lvl * 10) {}
    string getNom() const { return nom; }
    int getNiveau() const { return niveau; }
    int getPointsDeVie() const { return pointsDeVie; }
    void attaquer(Pokemon& cible);
    void subirDegats(int degats);
    bool estVivant() const { return pointsDeVie > 0; }
};

// Classe représentant un dresseur
class Dresseur {
private:
    string nom;
    vector<Pokemon> equipe;
public:
    Dresseur(string n) : nom(n) {}
    string getNom() const { return nom; }
    void ajouterPokemon(const Pokemon& p) { equipe.push_back(p); }
    bool aPokemonEnVie() const;
    Pokemon& choisirPokemonEnVie();
};

// Fonction pour simuler une attaque
void Pokemon::attaquer(Pokemon& cible) {
    int degats = niveau * 2;
    cout << nom << " attaque " << cible.getNom() << " et lui inflige " << degats << " points de dégâts." << endl;
    cible.subirDegats(degats);
}

// Fonction pour simuler une réception de dégâts
void Pokemon::subirDegats(int degats) {
    pointsDeVie -= degats;
    if (pointsDeVie < 0)
        pointsDeVie = 0;
    cout << nom << " a maintenant " << pointsDeVie << " points de vie restants." << endl;
}

// Vérifie si le dresseur a au moins un Pokémon en vie
bool Dresseur::aPokemonEnVie() const {
    for (const Pokemon& p : equipe) {
        if (p.estVivant())
            return true;
    }
    return false;
}

// Choix d'un Pokémon en vie aléatoire
Pokemon& Dresseur::choisirPokemonEnVie() {
    int index;
    do {
        index = rand() % equipe.size();
    } while (!equipe[index].estVivant());
    return equipe[index];
}

int main() {
    //générateur de nombres aléatoires
    srand(static_cast<unsigned int>(time(0)));


    Pokemon pikachu("Pikachu", 5);
    Pokemon bulbizarre("Bulbizarre", 5);
    Pokemon salameche("Salameche", 5);

    Dresseur red("Red");
    Dresseur blue("Blue");

    // Ajout des Pokémon dans les équipes des dresseurs
    red.ajouterPokemon(pikachu);
    blue.ajouterPokemon(bulbizarre);
    blue.ajouterPokemon(salameche);

    // Combat entre les dresseurs
    while (red.aPokemonEnVie() && blue.aPokemonEnVie()) {
        Pokemon& attaquant = red.choisirPokemonEnVie();
        Pokemon& cible = blue.choisirPokemonEnVie();
        attaquant.attaquer(cible);

        // Échange des rôles
        if (cible.estVivant()) {
            Pokemon& attaquant2 = blue.choisirPokemonEnVie();
            Pokemon& cible2 = red.choisirPokemonEnVie();
            attaquant2.attaquer(cible2);
        }
    }

    // Affichage du vainqueur
    if (red.aPokemonEnVie()) {
        cout << "Red remporte le combat !" << endl;
    } else {
        cout << "Blue remporte le combat !" << endl;
    }

    return 0;
}
