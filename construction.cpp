#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Pour simplifier
typedef string Forme   ;
typedef string Couleur ;

class Brique
{
private:
  Forme   forme   ;
  Couleur couleur ;

public:
  /*****************************************************
    Compléter le code à partir d'ici
  *******************************************************/

  Brique(Forme forme, Couleur couleur) : forme(forme), couleur(couleur) {}
  Brique() = delete;

  ostream& afficher(ostream& sortie) const {
    if (couleur.find_first_not_of("\t\n ") == string::npos) {
      sortie << forme;
    }
    else {
      sortie << "(" << forme << ", " << couleur << ")";
    }
    return sortie;
  }


};

ostream& operator<<(ostream& sortie, Brique const &b) {
  return b.afficher(sortie);
}

class Construction
{
  friend class Grader;

private:
  vector<vector<vector<Brique>>> contenu;

  unsigned int FindMaxHeight() {
    return contenu.size() - 1;
  }

public:
  Construction(Brique const &a) :
    contenu(vector<vector<vector<Brique>>>(1, vector<vector<Brique>>(1, vector<Brique>(1, a))))
  {
  }

  ostream& afficher(ostream& sortie) const {
    size_t isize = contenu.size();
    for (int i = isize - 1; i >= 0; i--) {
      sortie << "Couche " << (i) << " :" << endl;
      size_t jsize = contenu[i].size();
      for (int j = jsize - 1; j >= 0; j--) {
        size_t ksize = contenu[i][j].size();
        for (int k = ksize - 1; k >= 0; k--) {
          sortie << contenu[i][j][k];
          if (k > 0) {
            sortie << " ";
          }
        }
        if (!(i == 0 && j == 0)) {
          sortie << endl;
        }
      }
    }
    return sortie;
  }

  Construction& operator^=(Construction const &a) {
    contenu.insert(contenu.end(), a.contenu.begin(), a.contenu.end());
    return *this;
  }

  Construction& operator-=(Construction const &a) {
    size_t isize = contenu.size();
    size_t aisize = a.contenu.size();
    for (int i = 0; i < isize && i < aisize && aisize >= isize; i++) {
      contenu[i].insert(contenu[i].end(), a.contenu[i].begin(), a.contenu[i].end());
    }
    return *this;
  }

  Construction& operator+=(Construction const &a) {
    size_t isize = contenu.size();
    size_t aisize = a.contenu.size();
    for (int i = 0; i < isize && i < aisize && aisize >= isize; i++) {

      auto &icontenu = contenu[i];
      auto const &aicontenu = a.contenu[i];

      size_t jsize = icontenu.size();
      size_t ajsize = aicontenu.size();

      for (int j = 0; j < jsize && j < ajsize && ajsize >= jsize; j++) {

        auto &jcontenu = icontenu[j];
        auto const &ajcontenu = aicontenu[j];

        jcontenu.insert(jcontenu.begin(), ajcontenu.begin(), ajcontenu.end());
      }

    }
    return *this;
  }
};

ostream& operator<<(ostream& sortie, Construction const &b) {
  return b.afficher(sortie);
}

const Construction operator*(unsigned int n, Construction const& a)
{
  Construction b(a);
  for (int i = 1; i < n; i++) {
    b += a;
  }
  return b;
}

const Construction operator/(unsigned int n, Construction const& a)
{
  Construction b(a);
  for (int i = 1; i < n; i++) {
    b ^= a;
  }
  return b;
}

const Construction operator%(unsigned int n, Construction const& a)
{
  Construction b(a);
  for (int i = 1; i < n; i++) {
    b -= a;
  }
  return b;
}

Construction operator^(Construction a, Construction const &b) {
  return a ^= b;
}

Construction operator-(Construction a, Construction const &b) {
  return a -= b;
}

Construction operator+(Construction a, Construction const &b) {
  return a += b;
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  // Modèles de briques
  Brique toitD("obliqueD", "rouge");
  Brique toitG("obliqueG", "rouge");
  Brique toitM(" pleine ", "rouge");
  Brique mur  (" pleine ", "blanc");
  Brique vide ("                 ", "");

  unsigned int largeur(4);
  unsigned int profondeur(3);
  unsigned int hauteur(3); // sans le toit

  // on construit les murs
  Construction maison( hauteur / ( profondeur % (largeur * mur) ) );

  // on construit le toit
  Construction toit(profondeur % ( toitG + 2*toitM + toitD ));
  toit ^= profondeur % (vide + toitG + toitD);

  // on pose le toit sur les murs
  maison ^= toit;

  // on admire notre construction
  cout << maison << endl;

  return 0;
}
