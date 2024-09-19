#include "Derivee_Generic_station_parser.hpp"
#include "Generic_mapper.hpp"
#include "Grade.hpp"
using namespace std;
using namespace travel;
using travel::evaluate_small;
using travel::evaluate;



/**
La fonction Find_Path_By_ID permet de calculer le meilleur itinéraire pour aller d'une station a une autre en utilisant leurs identifiants
**/

void Find_Path_By_ID(Path & chemin) {

    std::cout << "Bonjour! Ou souhaitez vous aller? (Utilisez les identifiants des stations SVP) : "<<std::endl;
    // Créer les maps pour stocker les stations et les connexions
    unordered_map < uint64_t, Station > smap;
    unordered_map < uint64_t, unordered_map < uint64_t, uint64_t >> cmap;

    // Lire les données des fichiers CSV et les stocker dans les maps
    chemin.read_stations("s.csv");
    chemin.read_connections("c.csv");
    smap = chemin.get_stations_hashmap();
    cmap = chemin.get_connections_hashmap();

    // Demander à l'utilisateur d'entrer l'ID de la station de départ
    uint64_t start, end;
    do {
        cout << "Entrez l'identifiant de la station de depart : ";
        cin >> start;

        // Vérifier si l'ID est valide, sinon demander à nouveau
        if (smap.count(start) == 0) {
            cout << "L'identifiant de station n'existe pas, veuillez reessayer." << endl;
        }
    } while (smap.count(start) == 0);

    // Demander à l'utilisateur d'entrer l'ID de la station d'arrivée
    do {
        cout << "Entrez l'identifiant de la station d'arrivee : ";
        cin >> end;

        // Vérifier si l'ID est valide, sinon demander à nouveau
        if (smap.count(end) == 0) {
            cout << "L'identifiant de station n'existe pas, veuillez reessayer." << endl;
        }
    } while (smap.count(end) == 0);

    // Calculer le chemin entre les deux stations et l'afficher
    chemin.compute_and_display_travel(start, end);
}


/**
La fonction Find_Path_By_Name permet de calculer le meilleur itinéraire pour aller d'une station a une autre en utilisant les noms des stations
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

    // Demande à l'utilisateur d'entrer le nom de la station de départ et d'arrivée
    cout << "Entrez le nom de la station de depart : ";
    getline(cin, startName);
    cout << "Entrez le nom de la station d'arrivee : ";
    getline(cin, endName);


    // Calcul du trajet entre les deux stations et affichage du résultat
    chemin.compute_and_display_travel(startName, endName);

}




int main()
{
    /**
    Décommenter les lignes ci-dessous si vous souhaiter procéder à la lecture du fichier contenant les stations
    N'oubliez pas de décommenter la partie dédié à l'affichage dans la méthode associé dans le Derivee_Generic_station_parser.cpp
    **/
    
    //Path liste_stations;
    //liste_stations.read_stations("s.csv");
    //evaluate_small.stations(liste_stations);


     /**
    Décommenter les lignes ci-dessous si vous souhaiter procéder à la lecture du fichier contenant les connections
    N'oubliez pas de décommenter la partie dédié à l'affichage dans la méthode associé dans le Derivee_Generic_station_parser.cpp
    **/

     //Path liste_connections;
     //liste_connections.read_connections("c.csv");
     //evaluate_small.connections(liste_connections);
    /**
    Décommenter les lignes ci_dessous si vous souhaitez trouver le plus court chemin en deux stations en utilisant les identifiants
    **/

    Path chemin;
    Find_Path_By_ID(chemin);
    evaluate.dijkstra(chemin, false);

     /**
    Décommenter les lignes ci_dessous si vous souhaitez trouver le plus court chemin en deux stations en utilisant les noms
    **/

    //Path chemin;
    //Find_Path_By_Name(chemin);
    //evaluate.dijkstra(chemin, true);
  
    return 0;
}
