const char FICHIER_ACTIVITES[] = "Activites.txt";
const char FICHIER_INSCRIPTIONS[] = "Demandes.txt";
const int MAX_ACTIVITES = 5;
const int LONGUEUR_LIGNE = 100;

struct Membre;

struct Activite {
	char* code;				// Code de l'Activite
	char* titre;			// Titre de l'activit�
	int nbMaxParticipants;	// Nombre maximal de participants
	Activite* actSuivante;	// Activite suivante dans la liste
	/* Tableau dynamique de pointeurs sur les  membres inscrits, le nombre d'entr�es 
	   dans tabInscrits est d�termin� par le champ nbMaxParticipants */
	Membre** tabInscrits;	
};

struct Membre {
	char* noMembre;			// Num�ro du Membre
	char* prenom;			// Pr�nom du Membre
	char* nomFamille;		// Nom de famille du Membre
	// Tableau de pointeurs sur les activit�s auxquelles le Membre est inscrit
	Activite* tabActivites[MAX_ACTIVITES];	
	Membre* numeroSuivant;	// Participant suivant dans la liste par num�ro
	Membre* nomSuivant;		// Participant suivent dans la liste par nom
};

struct Demande {
	char* noMembre;		// Num�ro du Membre qui fait la Demande
	char* prenom;		// Pr�nom du Membre
	char* nomFamille;	// Nom de famille du Membre
	char* code;			// Code de l'Activite � laquelle il veut s'inscrire
	Demande* demandeSuivante;
};