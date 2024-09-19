#include "Derivee_Generic_station_parser.hpp"
#include "Generic_mapper.hpp"
#include "Grade.hpp"
using namespace std;
using namespace travel;
using travel::evaluate_small;
using travel::evaluate;



/**
La fonction Find_Path_By_ID permet de calculer le meilleur itin�raire pour aller d'une station a une autre en utilisant leurs identifiants
**/

void Find_Path_By_ID(Path & chemin) {

    std::cout << "Bonjour! Ou souhaitez vous aller? (Utilisez les identifiants des stations SVP) : "<<std::endl;
    // Cr�er les maps pour stocker les stations et les connexions
    unordered_map < uint64_t, Station > smap;
    unordered_map < uint64_t, unordered_map < uint64_t, uint64_t >> cmap;

    // Lire les donn�es des fichiers CSV et les stocker dans les maps
    chemin.read_stations("s.csv");
    chemin.read_connections("c.csv");
    smap = chemin.get_stations_hashmap();
    cmap = chemin.get_connections_hashmap();

    // Demander � l'utilisateur d'entrer l'ID de la station de d�part
    uint64_t start, end;
    do {
        cout << "Entrez l'identifiant de la station de depart : ";
        cin >> start;

        // V�rifier si l'ID est valide, sinon demander � nouveau
        if (smap.count(start) == 0) {
            cout << "L'identifiant de station n'existe pas, veuillez reessayer." << endl;
        }
    } while (smap.count(start) == 0);

    // Demander � l'utilisateur d'entrer l'ID de la station d'arriv�e
    do {
        cout << "Entrez l'identifiant de la station d'arrivee : ";
        cin >> end;

        // V�rifier si l'ID est valide, sinon demander � nouveau
        if (smap.count(end) == 0) {
            cout << "L'identifiant de station n'existe pas, veuillez reessayer." << endl;
        }
    } while (smap.count(end) == 0);

    // Calculer le chemin entre les deux stations et l'afficher
    chemin.compute_and_display_travel(start, end);
}


/**
La fonction Find_Path_By_Name permet de calculer le meilleur itin�raire pour aller d'une station a une autre en utilisant les noms des stations
**/

void Find_Path_By_Name(Path & chemin) {

     std::cout << "Bonjour! Ou souhaitez vous aller? (Utilisez les noms des stations SVP) : "<<std::endl;

    string startName = "s"; // initialisation de la variable de nom de depart
    string endName = "e"; // initialisation de la variable de nom d'arrivee

    // Initialisation de deux unordered_map qui vont contenir les informations sur les stations et les connexions
    unordered_map < uint64_t, Station > smap;
    unordered_map < uint64_t, unordered_map < uint64_t, uint64_t >> cmap;

    // Lecture des fichiers CSV contenant les informations sur les stations et les connexions, et stockage des informations dans les unordered_map correspondants
    chemin.read_stations("s.csv");
    chemin.read_connections("c.csv");
    smap = chemin.get_stations_hashmap();
    cmap = chemin.get_connections_hashmap();

    // Demande � l'utilisateur d'entrer le nom de la station de d�part et d'arriv�e
    cout << "Entrez le nom de la station de depart : ";
    getline(cin, startName);
    cout << "Entrez le nom de la station d'arrivee : ";
    getline(cin, endName);


    // Calcul du trajet entre les deux stations et affichage du r�sultat
    chemin.compute_and_display_travel(startName, endName);

}




int main()
{
    /**
    D�commenter les lignes ci-dessous si vous souhaiter proc�der � la lecture du fichier contenant les stations
    N'oubliez pas de d�commenter la partie d�di� � l'affichage dans la m�thode associ� dans le Derivee_Generic_station_parser.cpp
    **/
    
    //Path liste_stations;
    //liste_stations.read_stations("s.csv");
    //evaluate_small.stations(liste_stations);


     /**
    D�commenter les lignes ci-dessous si vous souhaiter proc�der � la lecture du fichier contenant les connections
    N'oubliez pas de d�commenter la partie d�di� � l'affichage dans la m�thode associ� dans le Derivee_Generic_station_parser.cpp
    **/

     //Path liste_connections;
     //liste_connections.read_connections("c.csv");
     //evaluate_small.connections(liste_connections);
    /**
    D�commenter les lignes ci_dessous si vous souhaitez trouver le plus court chemin en deux stations en utilisant les identifiants
    **/

    Path chemin;
    Find_Path_By_ID(chemin);
    evaluate.dijkstra(chemin, false);

     /**
    D�commenter les lignes ci_dessous si vous souhaitez trouver le plus court chemin en deux stations en utilisant les noms
    **/

    //Path chemin;
    //Find_Path_By_Name(chemin);
    //evaluate.dijkstra(chemin, true);
  
    return 0;
}
