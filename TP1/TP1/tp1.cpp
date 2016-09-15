#include <iostream>
#include <fstream>
#include <locale>
#include <stdio.h>
#include <string.h>
using namespace std;
#include "TP1.h"

void menu();
void fichierActivites(Activite *&listeActivites);
void insereAct(Activite *&listeActivites, char titre[LONGUEUR_LIGNE], char cod[LONGUEUR_LIGNE], int nb);
void afficherAct(Activite *listeActivites, Membre *&listeMembresNom);
void fichierDemande(Membre *&listeMembresNom, Membre *&listeMembresNumero, Activite *&listeActivites);
void insereTabActiv(Membre *&listeMembresNom, Membre *&listeMembresNumero, Activite *&listeActivites, char numero[LONGUEUR_LIGNE], char prenom[LONGUEUR_LIGNE], char nom[LONGUEUR_LIGNE], char code[LONGUEUR_LIGNE]);
void insereNomNumero(Membre *&listeMembresNom, Membre *&listeMembresNumero, Activite *&listeActivites, char numero[LONGUEUR_LIGNE], char prenom[LONGUEUR_LIGNE], char nom[LONGUEUR_LIGNE], char code[MAX_ACTIVITES]);
void afficherNom(Membre* listeMembresNom);
void affichageInscription(Activite *&listeActivites);
void afficherNumero(Membre* listeMembresNumero);
void afficherMember(Membre *&listeMembresNom);
void inscriptionAttent(Activite *&listeActivites, Membre *&listeMembresNom, Demande *&demandesEnAttente);
void afficherAttente(Demande* demandesEnAttente);
void demandeInscription(Activite *&listeActivites, Demande *&demandesEnAttente);
void insereDemend(Demande *&demandesEnAttente, char numero[LONGUEUR_LIGNE], char prenom[LONGUEUR_LIGNE], char nom[LONGUEUR_LIGNE], char code[MAX_ACTIVITES]);
void annulerInscription(Demande *&demandesEnAttente);
void annulerDemend(Demande *&demandesEnAttente, char code[LONGUEUR_LIGNE], char numero[LONGUEUR_LIGNE]);

void main() {
	setlocale(LC_ALL, "");
	Activite* listeActivites = NULL;
	Membre* listeMembresNumero = NULL;
	Membre* listeMembresNom = NULL;
	Demande* demandesEnAttente = NULL;
	int valeur;

	fichierActivites(listeActivites);
	fichierDemande(listeMembresNom, listeMembresNumero, listeActivites);
	//inscriptionAttent(listeActivites, listeMembresNom, demandesEnAttente);
	menu();
	cin >> valeur;
	while (valeur != 0) {
		switch (valeur - 1) {
		case 0:
			afficherAct(listeActivites, listeMembresNom);
			break;
		case 1:
			afficherNom(listeMembresNom);
			break;
		case 2:
			afficherNumero(listeMembresNumero);
			break;
		case 3:
			affichageInscription(listeActivites);
			break;
		case 4:
			afficherMember(listeMembresNom);
			break;
		case 5:
			afficherAttente(demandesEnAttente);
			break;
		case 6:
			demandeInscription(listeActivites, demandesEnAttente);
			break;
		case 7:
			annulerInscription(demandesEnAttente);
			break;
			;
		}
		menu();//aficher menu
		cin >> valeur;//lire le choix sur clavier
	}
	system("pause");

}
//methode qui afiche la menu
void menu(){
	cout << "------------------------" << endl;
	cout << "          MENU          " << endl;
	cout << "------------------------" << endl;
	cout << "1 - Produire la liste des activités" << endl;
	cout << "2 - Produire la liste des membres par ordre de nom" << endl;
	cout << "3 - Produire la liste des membres par ordre de numéro" << endl;
	cout << "4 - Produire la liste des inscriptions par activité" << endl;
	cout << "5 - Produire la liste des activités auxquelles est inscrit un participant" << endl;
	cout << "6 - Produire la liste des demandes d'inscription en attente" << endl;
	cout << "7 - Ajouter des demandes d'inscription" << endl;
	cout << "8 - Annuler des inscriptions" << endl;
	cout << endl;
	cout << "0 - Quitter l'application" << endl;
	cout << endl;
	cout << endl;
	cout << "Faites votre choix : ";
}
//methode qui lite le fichier Activités.txt
void fichierActivites(Activite *&listeActivites) {
	char titre_act[LONGUEUR_LIGNE];   //la titre d'activité
	char cod_act[LONGUEUR_LIGNE];    //la code d'activité
	char nb_char[LONGUEUR_LIGNE];   //la nombre d'activité
	int nb;                        //pour int de nombre d'activité

	ifstream lectureActiv;
	lectureActiv.open(FICHIER_ACTIVITES, ios::in);

	if (lectureActiv.fail()) {
		cout << "Erreur d'ouverture du fichier input" << endl;
		exit(1);
	}
	lectureActiv.getline(titre_act, LONGUEUR_LIGNE, '/');
	while (!lectureActiv.eof()) {
		lectureActiv.getline(cod_act, LONGUEUR_LIGNE, '/');
		lectureActiv.getline(nb_char, LONGUEUR_LIGNE);
		nb = atol(nb_char);

		insereAct(listeActivites, titre_act, cod_act, nb);
		lectureActiv.getline(titre_act, LONGUEUR_LIGNE, '/');
	}
	lectureActiv.close();
}
//methode qui insere l'information dans la liste d'activités
void insereAct(Activite *&listeActivites, char titre[LONGUEUR_LIGNE], char cod[LONGUEUR_LIGNE], int nb) {
	Activite *p = new Activite;
	if (p == NULL){
		exit(EXIT_FAILURE);
	}
	else {
		Activite *p_tmp = NULL;
		Activite *p_tete = listeActivites;
		p->titre = new char[LONGUEUR_LIGNE];
		strcpy_s(p->titre, LONGUEUR_LIGNE, titre);
		p->code = new char[LONGUEUR_LIGNE];
		strcpy_s(p->code, LONGUEUR_LIGNE, cod);
		p->nbMaxParticipants = nb;
		p->tabInscrits = new Membre*[nb];
		for (int i = 0; i < nb; i++){
			p->tabInscrits[i] = NULL;
		}
		p->actSuivante = NULL;
		while (p_tete != NULL && (int)p_tete->code[0] <= (int)cod[0])
		{
			p_tmp = p_tete;
			p_tete = p_tete->actSuivante;
		}
		p->actSuivante = p_tete;
		if (p_tmp != NULL)
		{
			p_tmp->actSuivante = p;
		}
		else
		{
			listeActivites = p;
		}
	}
}
//afficher la liste d'activités dans l'option 1
void afficherAct(Activite *listeActivites, Membre *&listeMembresNom){
	int comp = 0;//compteur
	int place;//les places disponibles
	cout << endl;
	cout << endl;
	cout << "Liste des activités" << endl;
	cout << "--------------------" << endl;
	cout << endl;
	if (listeActivites == NULL)
	{
		exit(EXIT_FAILURE);
	}
	Activite *p = listeActivites;
	while (p != NULL)
	{
		cout << p->code << " : " << p->titre << endl;
		cout << "        Nombre maximale de participants : " << p->nbMaxParticipants << endl;
		comp = 0;
		Membre *m = listeMembresNom;
		while (m != NULL)
		{
			for (int i = 0; i < MAX_ACTIVITES && m->tabActivites[i] != NULL; i++){
				if (p->code == m->tabActivites[i]->code){
					++comp;
				}
			}
			m = m->nomSuivant;
		}
		if (p->nbMaxParticipants - comp < 0){
			place = 0;
		}
		else{
			place = p->nbMaxParticipants - comp;
		}
		cout << "        Nombre de place(s) disponible(s) : " << place << endl;
		cout << endl;
		p = p->actSuivante;
	}
	cout << endl;
}
//lire fichier de Demend.txt
void fichierDemande(Membre *&listeMembresNom, Membre *&listeMembresNumero, Activite *&listeActivites) {
	char prenom[LONGUEUR_LIGNE];        //prenom du membre
	char nom[LONGUEUR_LIGNE];          //nom du membre
	char numero[LONGUEUR_LIGNE];      //numero du membre
	char code[LONGUEUR_LIGNE];       //code du membre

	ifstream lectureDemande;
	lectureDemande.open(FICHIER_INSCRIPTIONS, ios::in);

	if (lectureDemande.fail()) {
		cout << "Erreur d'ouverture du fichier input" << endl;
		exit(1);
	}
	lectureDemande.getline(numero, LONGUEUR_LIGNE, '/');
	while (!lectureDemande.eof()) {

		lectureDemande.getline(prenom, LONGUEUR_LIGNE, '/');
		lectureDemande.getline(nom, LONGUEUR_LIGNE, '/');
		lectureDemande.getline(code, LONGUEUR_LIGNE);
		insereTabActiv(listeMembresNom, listeMembresNumero, listeActivites, numero, prenom, nom, code);
		lectureDemande.getline(numero, LONGUEUR_LIGNE, '/');
	}
	lectureDemande.close();
}
//methode qui insere la liste de membre du nom et la liste de membre de numero 
void insereTabActiv(Membre *&listeMembresNom, Membre *&listeMembresNumero, Activite *&listeActivites, char numero[LONGUEUR_LIGNE], char prenom[LONGUEUR_LIGNE],
	char nom[LONGUEUR_LIGNE], char code[MAX_ACTIVITES]) {
	bool areter = false;//pour areter le boucle qui ramplire tabActiviter 
	bool ver_nom = false;//pour savoir si le meembre existe dans la liste
	Membre *p_mem = NULL;
	Membre*p_tete = listeMembresNom;
	if (p_tete != NULL){
		while (p_tete != NULL) {
			if (strcmp(p_tete->noMembre, numero) == 0 && !ver_nom){
				ver_nom = true;
				p_mem = p_tete;
			}
			p_tete = p_tete->nomSuivant;
		}
		if (ver_nom == true){
			Activite* a_tete = listeActivites;
			while (a_tete != NULL) {
				if (strcmp(a_tete->code, code) == 0){
					for (int i = 0; i < MAX_ACTIVITES && !areter; i++){
						if (p_mem->tabActivites[i] == NULL){
							p_mem->tabActivites[i] = new Activite;
							p_mem->tabActivites[i] = a_tete;
							areter = true;
						}
					}
				}
				a_tete = a_tete->actSuivante;
			}
		}
		else {
			insereNomNumero(listeMembresNom, listeMembresNumero, listeActivites, numero, prenom, nom, code);
		}
	}
	else {
		insereNomNumero(listeMembresNom, listeMembresNumero, listeActivites, numero, prenom, nom, code);
	}
}
//method qui faire 2-em partie de insertion de membre
void insereNomNumero(Membre *&listeMembresNom, Membre *&listeMembresNumero, Activite *&listeActivites, char numero[LONGUEUR_LIGNE], char prenom[LONGUEUR_LIGNE],
	char nom[LONGUEUR_LIGNE], char code[MAX_ACTIVITES]){
	Membre *p_tmp = NULL;
	Membre*p_tete = listeMembresNom;
	Membre*num_tete = listeMembresNumero;
	Membre* p = new Membre;
	for (int i = 0; i < MAX_ACTIVITES; i++){
		p->tabActivites[i] = NULL;
	}
	p->noMembre = new char[LONGUEUR_LIGNE];
	strcpy_s(p->noMembre, LONGUEUR_LIGNE, numero);
	p->prenom = new char[LONGUEUR_LIGNE];
	strcpy_s(p->prenom, LONGUEUR_LIGNE, prenom);
	p->nomFamille = new char[LONGUEUR_LIGNE];
	strcpy_s(p->nomFamille, LONGUEUR_LIGNE, nom);
	Activite* a_tete = listeActivites;
	while (a_tete != NULL){
		if (strcmp(a_tete->code, code) == 0){
			p->tabActivites[0] = a_tete;
		}
		a_tete = a_tete->actSuivante;
	}
	////////////insere la liste de Nom////////////////////
	p->nomSuivant = NULL;
	while (p_tete != NULL && (int)p_tete->nomFamille[0] <= (int)nom[0])
		//while (p_tete != NULL && strcmp(p_tete->nomFamille, nom) < 0)
	{
		p_tmp = p_tete;
		p_tete = p_tete->nomSuivant;
	}
	p->nomSuivant = p_tete;
	if (p_tmp != NULL)
	{
		p_tmp->nomSuivant = p;
	}
	else
	{
		listeMembresNom = p;
	}
	///////////insere la liste de Numero////////////////
	while (num_tete != NULL && (int)num_tete->noMembre[2] <= (int)numero[2])
		//while (num_tete != NULL && strcmp(num_tete->noMembre, numero) < 0)
	{
		p_tmp = num_tete;
		num_tete = num_tete->numeroSuivant;
	}
	p->numeroSuivant = num_tete;
	if (p_tmp != NULL)
	{
		p_tmp->numeroSuivant = p;
	}
	else
	{
		listeMembresNumero = p;
	}
}
// methode qui affiche la liste de membres par nom, option 2
void afficherNom(Membre* listeMembresNom){
	int comp = 0;    //compteur
	cout << endl;
	cout << endl;
	cout << "Liste des membres par nom" << endl;
	cout << "------------------------------" << endl;
	cout << endl;
	if (listeMembresNom == NULL)
	{
		exit(EXIT_FAILURE);
	}
	Membre *p = listeMembresNom;
	while (p != NULL)
	{
		cout << p->nomFamille << " " << p->prenom << " - " << p->noMembre << endl;
		p = p->nomSuivant;
		++comp;
	}
	cout << endl;
	cout << "Nombre de memberes = " << comp << endl;
	cout << endl;
	cout << "--------------------------" << endl;
	cout << endl;
}
// methode qui affiche la liste des membres par numero, option 3
void afficherNumero(Membre* listeMembresNumero){
	int comp = 0;    //compteur
	cout << endl;
	cout << endl;
	cout << "Liste des membres par numero" << endl;
	cout << "------------------------------" << endl;
	cout << endl;
	if (listeMembresNumero == NULL)
	{
		exit(EXIT_FAILURE);
	}
	Membre *p = listeMembresNumero;
	while (p != NULL)
	{
		cout << p->noMembre << " - " << p->prenom << " " << p->nomFamille << endl;
		p = p->numeroSuivant;
		++comp;
	}
	cout << endl;
	cout << "Nombre de memberes = " << comp << endl;
	cout << endl;
	cout << "--------------------------" << endl;
	cout << endl;
}
//methode qui affiche la liste des inscription à toutes les activités, option 4
void affichageInscription(Activite *&listeActivites){
	int comp = 0; //compteur
	int place = 0; //nombre place encore disponible
	cout << endl;
	cout << "Liste des inscriptions par activités" << endl;
	cout << "------------------------------------" << endl;
	cout << endl;
	if (listeActivites == NULL)
	{
		exit(EXIT_FAILURE);
	}
	Activite *p = listeActivites;
	while (p != NULL)
	{
		comp = 0;
		cout << p->code << " : " << p->titre << endl;
		for (int i = 0; i < p->nbMaxParticipants && p->tabInscrits[i] != NULL; ++i){
			cout << "        " << p->tabInscrits[i]->prenom << " " << p->tabInscrits[i]->nomFamille << " - " << p->tabInscrits[i]->noMembre << endl;
			++comp;
		}
		place = p->nbMaxParticipants - comp;
		if (comp > p->nbMaxParticipants){
			place = 0;
		}
		cout << endl;
		cout << "Nombre d'inscrits à l'activité =  " << comp << endl;
		cout << "Nombre de place(s) encore disponible(s) =  " << place << endl;
		cout << endl;
		p = p->actSuivante;
	}
	cout << endl;
}
//methode qui affiche les activites du membre, option 5
void afficherMember(Membre *&listeMembresNom){
	int len;   //pour le longeur de chaine numero
	bool aret = false;   //pour areter la boucle
	char numero[LONGUEUR_LIGNE];  //le numero du membre
	int comp = 0;   //compteur
	cout << "Entrez le numero du membre  ";
	cin.clear(); // Nettoyer le flux
	cin.ignore(cin.rdbuf()->in_avail()); // Vider le buffer
	cin.getline(numero, LONGUEUR_LIGNE);
	len = strlen(numero);
	if (len == 0){
		cout << endl;
		cout << "Liste des inscription de tous les membres" << endl;
		cout << "-----------------------------------------" << endl;
		cout << endl;
	}
	Membre *p = listeMembresNom;
	while (p != NULL && !aret)
	{
		if (len == 0){
			cout << endl;
			cout << "Membre " << p->noMembre << " " << p->prenom << " " << p->nomFamille << endl;
			cout << endl;
			comp = 0;
			for (int i = 0; i < MAX_ACTIVITES && p->tabActivites[i] != NULL; i++){
				cout << p->tabActivites[i]->code << " " << p->tabActivites[i]->titre << endl;
				++comp;
			}
			cout << endl;
			cout << "Nombre d'activite auxquelles est inscrit le Membre = " << comp << endl;
			cout << endl;
		}
		else{
			if (strcmp(p->noMembre, numero) == 0){
				cout << endl;
				cout << "Liste des activites" << endl;
				cout << "Membre " << p->noMembre << " " << p->prenom << " " << p->nomFamille << endl;
				cout << endl;
				comp = 0;
				for (int i = 0; i < MAX_ACTIVITES && p->tabActivites[i] != NULL; i++){
					cout << p->tabActivites[i]->code << " " << p->tabActivites[i]->titre << endl;
					++comp;
				}
				cout << endl;
				cout << "Nombre d'activite auxquelles est inscrit le Membre = " << comp << endl;
				cout << endl;
				aret = true;
			}
		}

		p = p->nomSuivant;
	}
	if (aret == false && len != 0){
		cout << endl;
		cout << "Numero de membre inexistant" << endl;
		cout << endl;
		cout << endl;
	}
}
// methode qui insere la liste de demende et les members inscrite pour chaque activites
void inscriptionAttent(Activite *&listeActivites, Membre *&listeMembresNom, Demande *&demandesEnAttente){
	Activite *p_tete = listeActivites;
	Activite *p = new Activite;

	while (p_tete != NULL)
	{
		int comp = 0;
		Membre *m = listeMembresNom;
		while (m != NULL)
		{
			for (int i = 0; i < MAX_ACTIVITES && m->tabActivites[i] != NULL; i++){
				if (p_tete->code == m->tabActivites[i]->code){
					++comp;
					bool areter = false;
					for (int i = 0; i < p_tete->nbMaxParticipants && areter == false; i++){
						if (p_tete->tabInscrits[i] == NULL){
							p_tete->tabInscrits[i] = m;
							areter = true;
						}
					}
					if (comp > p_tete->nbMaxParticipants){
						Demande *p = new Demande;
						if (p == NULL){
							exit(EXIT_FAILURE);
						}
						else {
							Demande *p_tmp = NULL;
							Demande *p_tete = demandesEnAttente;
							p->demandeSuivante = NULL;
							p->noMembre = m->noMembre;
							p->nomFamille = m->nomFamille;
							p->prenom = m->prenom;
							p->code = m->tabActivites[i]->code;

							p->demandeSuivante = NULL;
							if (demandesEnAttente == NULL)
							{
								demandesEnAttente = p;
							}
							else
							{
								Demande *temp = demandesEnAttente;
								while (temp->demandeSuivante != NULL)
								{
									temp = temp->demandeSuivante;
								}
								temp->demandeSuivante = p;
							}
						}
					}
				}
			}
			m = m->nomSuivant;
		}
		p_tete = p_tete->actSuivante;
	}
}
// methode qui affiche les membres en attente
void afficherAttente(Demande* demandesEnAttente){
	int comp = 0;//compteur
	Demande *p = demandesEnAttente;
	cout << endl;
	cout << endl;
	cout << "Liste des demandes en attente" << endl;
	cout << "------------------------------" << endl;
	cout << endl;
	if (demandesEnAttente == NULL)
	{
		cout << "Liste des demandes en attente est vide" << endl;
		cout << endl;
	}
	else{
		while (p != NULL)
		{
			cout << p->prenom << " " << p->nomFamille << " - " << p->noMembre << endl;
			p = p->demandeSuivante;
			++comp;
		}
		cout << endl;
		cout << "Nombre de demandes = " << comp << endl;
		cout << endl;
		cout << "--------------------------" << endl;
		cout << endl;
	}
}
// methode qui faire inscription un person pour l'activite
void demandeInscription(Activite *&listeActivites, Demande *&demandesEnAttente){
	char prenom[LONGUEUR_LIGNE]; //prenom de la personne
	char nom[LONGUEUR_LIGNE];   //nom de la personne
	char numero[LONGUEUR_LIGNE];  //numero de la personne
	char code[LONGUEUR_LIGNE];   //code de la personne
	bool activite = false;   // pour arter la boucle de l'activite
	bool exist = false;   // pour areter la boucle de membre
	cout << endl;
	cout << "--------------" << endl;
	cout << "Entrez votre code de l'activite  ";
	cin >> code;
	cout << endl;
	cout << "Entrez votre numero de membre  ";
	cin >> numero;
	cout << endl;
	cout << "Entrez votre prenom  ";
	cin >> prenom;
	cout << endl;
	cout << "Entrez votre nom  ";
	cin >> nom;
	cout << endl;
	Activite *p = listeActivites;
	while (p != NULL)
	{
		if (strcmp(p->code, code) == 0){
			activite = true;
		}
		p = p->actSuivante;
	}
	if (activite == false){
		cout << "Activite que vous voulez etre inscrit n'existe pas" << endl;
	}
	else{
		Demande *p_tete = demandesEnAttente;
		while (p_tete != NULL)
		{
			if (strcmp(p_tete->code, code) == 0 && strcmp(p_tete->noMembre, numero) == 0){
				exist = true;
			}
			p_tete = p_tete->demandeSuivante;
		}
		if (exist == true){
			cout << "Vous ne'pouvez pas demander l'inscription parce que  " << prenom << " " << nom << " deja demander inscription pour cette activité" << endl;
		}
		else{
			insereDemend(demandesEnAttente, numero, prenom, nom, code);
			cout << endl;
			cout << prenom << " " << nom << " - Vous etes dans la liste attende!" << endl;
		}
	}
}
// methode qui ajoute un memebre dans la liste attente
void insereDemend(Demande *&demandesEnAttente, char numero[LONGUEUR_LIGNE], char prenom[LONGUEUR_LIGNE], char nom[LONGUEUR_LIGNE], char code[MAX_ACTIVITES]){
	Demande *p = new Demande;
	if (p == NULL){
		exit(EXIT_FAILURE);
	}
	else {
		Demande *p_tmp = NULL;
		Demande *p_tete = demandesEnAttente;
		p->noMembre = new char[LONGUEUR_LIGNE];
		strcpy_s(p->noMembre, LONGUEUR_LIGNE, numero);
		p->code = new char[LONGUEUR_LIGNE];
		strcpy_s(p->code, LONGUEUR_LIGNE, code);
		p->prenom = new char[LONGUEUR_LIGNE];
		strcpy_s(p->prenom, LONGUEUR_LIGNE, prenom);
		p->nomFamille = new char[LONGUEUR_LIGNE];
		strcpy_s(p->nomFamille, LONGUEUR_LIGNE, nom);

		p->demandeSuivante = NULL;
		if (demandesEnAttente == NULL)
		{
			demandesEnAttente = p;
		}
		else
		{
			Demande *temp = demandesEnAttente;
			while (temp->demandeSuivante != NULL)
			{
				temp = temp->demandeSuivante;
			}
			temp->demandeSuivante = p;
		}
	}
}
// methode qui demende les donnes de la membre qui veut annuler inscription
void annulerInscription(Demande *&demandesEnAttente){
	char numero[LONGUEUR_LIGNE]; //numero de la membre
	char code[LONGUEUR_LIGNE];  //code de la membre
	bool activite = false; //pour areter la boucle de l'activite
	bool annuler = false;  //pour verifier annulation
	cout << endl;
	cout << "Annulation d'inscription" << endl;
	cout << "------------------------" << endl;
	cout << endl;
	cout << "Entrez votre code de l'activite  ";
	cin >> code;
	cout << endl;
	cout << "Entrez votre numero de membre  ";
	cin >> numero;
	cout << endl;
	Demande *p = demandesEnAttente;
	while (p != NULL)
	{
		if (strcmp(p->code, code) == 0 && strcmp(p->noMembre, numero) == 0){
			activite = true;
		}
		p = p->demandeSuivante;
	}
	if (activite == false){
		cout << "Inscription que vous voulez annuler n'existe pas" << endl;
	}
	else{
		annulerDemend(demandesEnAttente, code, numero);
		while (p != NULL)
		{
			if (strcmp(p->code, code) == 0 && strcmp(p->noMembre, numero) == 0){
				annuler = true;
			}
			p = p->demandeSuivante;
		}
		if (annuler == true){
			cout << "Inscription que vous voulez annuler échoué !" << endl;
		}
		else{
			cout << endl;
			cout << " L'inscription pour le membre -" << numero << "ets annuler !" << endl;
		}

	}
}
// methode qui enleve le membre dans la liste de demande l'inscription
void annulerDemend(Demande *&demandesEnAttente, char code[LONGUEUR_LIGNE], char numero[LONGUEUR_LIGNE]){
	Demande *p_tmp = NULL;
	Demande *p_tete = demandesEnAttente;
	//p_tete->demandeSuivante = NULL;
	if (demandesEnAttente == NULL)
	{
		cout << "Le fichier d'inscription est vide" << endl;
	}
	else
	{
		if (strcmp(p_tete->code, code) == 0 && strcmp(p_tete->noMembre, numero) == 0){
			p_tete = p_tete->demandeSuivante;
			free(p_tete);
			demandesEnAttente = p_tete;
		}
		while (p_tete != NULL)
		{
			if (strcmp(p_tete->demandeSuivante->code, code) == 0 && strcmp(p_tete->demandeSuivante->noMembre, numero) == 0){
				p_tmp = p_tete->demandeSuivante;
				p_tete->demandeSuivante = p_tete->demandeSuivante->demandeSuivante;
				free(p_tmp);
				//break;
			}
			p_tete = p_tete->demandeSuivante;
		}
	}
}





