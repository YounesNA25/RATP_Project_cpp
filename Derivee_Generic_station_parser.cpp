#include "Derivee_Generic_station_parser.hpp"

/** M�thode qui permet de lire les fichiers stations.csv et s.csv contenant les stations de m�tro de RATP, et qui permet de stocker les
//informations dans le conteneur std::unordered_map
**/

void Path::read_stations(const std::string& _filename) {
    std::ifstream in(_filename);
    if (!in) {
        std::cerr << "Impossible d'acceder au fichier ! " << _filename << std::endl;
        return;
    }

    std::string line;
    std::string s;
    std::getline(in, line);
    while (std::getline(in, line)) {

        Station station;
        uint32_t station_id;
        std::istringstream str(line);
        std::getline(str, station.name, ',');
        getline(str, s, ',');
        station_id = atoi(s.c_str());
        std::getline(str, station.line_id, ',');
        std::getline(str, station.address,',');
        std::getline(str, station.line_name, ',');


        this -> stations_hashmap.insert({station_id,station});
    }
    in.close();

    /** D�commenter cette partie si vous souhaitez afficher les stations **/
    /*
    std::for_each(std::begin(this->stations_hashmap), std::end(this->stations_hashmap),
        [](const auto& kv) {
            std::cout << kv.first << " : " << kv.second << std::endl;
        });*/
}




/** M�thode qui permet de lire les fichiers connections.csv et c.csv contenant les coonections des m�tros de la RATP, et qui permet de stocker les
//informations dans le conteneur std::unordered_map
**/

void Path::read_connections(const std::string& _filename)
{
    std::ifstream in(_filename);
    if(!in){
        std::cerr << "Impossible d'acceder au fichier"<<std::endl;
        return;
    }

    std::string line;
    std::unordered_map<uint64_t, std::unordered_map<uint64_t, uint64_t>> connections;

    std::getline(in, line);
    while (std::getline(in, line)) {
        uint64_t from_stop_id;
        uint64_t to_stop_id;
        uint64_t min_transfer_time;

        std::istringstream str(line);

        std::string from_stop_id_str,to_stop_id_str, min_transfer_time_str;

        std::getline(str, from_stop_id_str, ',');
        std::getline(str, to_stop_id_str, ',');
        std::getline(str, min_transfer_time_str, '\n');


        from_stop_id = std::stoull(from_stop_id_str.c_str());
        to_stop_id =  std::stoull(to_stop_id_str.c_str());
        min_transfer_time = std::stoull(min_transfer_time_str.c_str());



        if (connections_hashmap.count(from_stop_id)) {
            this->connections_hashmap.at(from_stop_id)[to_stop_id] = min_transfer_time;
        }

        else {
            std::unordered_map<uint64_t,uint64_t> temp_hashmap;
            temp_hashmap[to_stop_id] = min_transfer_time;
            this->connections_hashmap[from_stop_id] = temp_hashmap;
        }
    }

    in.close();


    // Affichage des connections
    std::cout<<std::endl;
    // Parcours et affichage des donn�es
    /**
    On Affiche les donn�es comme ceci :
    - identifiant station de d�part:
       -identifiants stations qui peuvent etre desservies et temps de trajet
    **/
    /*for (const auto& kv : connections_hashmap) {
        std::cout << "- from station with id : " << kv.first << std::endl;
        for (const auto& sub_kv : kv.second) {
            //std::cout << "- from station with id : " << kv.first << "       - to station with id : " << sub_kv.first << ", time : " << sub_kv.second << std::endl;
            std::cout<< "       - to station with id : " << sub_kv.first << ", tavel time : " << sub_kv.second << std::endl;
        }
    }*/
}


/** compute_travel utilise l'algorithme Dijktra pour calculer le plus court chemin
// prend deux param�tres _start et _end, qui repr�sentent les stations de d�part et d'arriv�e, respectivement.
// Elle renvoie un vecteur de paires, o� chaque paire repr�sente une station et son co�t associ�.
// Le vecteur repr�sente le plus court chemin de la station de d�part � la station d'arriv�e**/

std::vector<std::pair<uint64_t, uint64_t>> Path::compute_travel(uint64_t _start, uint64_t _end) {

    // cr�ation d'une map vide qui stockera les stations visit�es et leur cout actuel
    std::unordered_map<uint64_t, uint64_t> visited_stations;

    // cr�ation d'une map vide qui stockera les stations non visit�s et leur cout actuel
    std::unordered_map<uint64_t, uint64_t> unvisited_stations;

    // cr�ation d'une map vide qui stockera tous les chemins vers une station
    std::unordered_map<uint64_t, std::vector<std::pair<uint64_t, uint64_t>>> all_paths_to_station;

    // cr�ation d'un vecteur vide qui sera remplis par le chemin actuel
    std::vector<std::pair<uint64_t, uint64_t>> the_path;

    // noeud de d�part et son cout de 0
    the_path.push_back({_start, 0});

    // On ajoute le chemin de d�part � la liste des chemins
    for (auto i = stations_hashmap.begin(); i != stations_hashmap.end(); i++) {
        all_paths_to_station.insert({i->first, the_path});
    }

    // On rajoute la station de d�part � la map des stations visit�s et on on initialise � 0 son cout
    visited_stations.insert({_start, 0});

    // Conteneur qui contient toutes les stations du graphe qui n'ont pas encore �t� visit�s et leurs couts depuis la station de d�part
    unvisited_stations = connections_hashmap[_start];

    //On initialise toutes les station non visit�s a un uint64 tr�s grand
    for (auto i = stations_hashmap.begin(); i != stations_hashmap.end(); i++) {
        uint64_t value = 10000000;
        uint64_t station_id = i->first;
        if (station_id != _start) {
            unvisited_stations.insert({station_id, value});
        }
    }

    // On parcourt l'ensemble des stations non visit�s et on compare le cout actuel avec le cout minimum trouv� jusqu'a pr�sent
    while (unvisited_stations.size() > 0) {
        std::pair<uint64_t, uint64_t> min_value;
        min_value.second = 10000000;
        for (auto i = unvisited_stations.begin(); i != unvisited_stations.end(); i++) {
            if (i->second < min_value.second) {
                min_value.first = i->first;
                min_value.second = i->second;
            }
        }

        //On rajoute la station la plus proche parmi celles visit�s
        visited_stations.insert(min_value);
        // on suuprime la station visit� de celle qui n'ont pas encore �t� visit�s
        unvisited_stations.erase(min_value.first);


        the_path = all_paths_to_station.at(min_value.first);
        the_path.push_back(min_value);
        // on supprime l'ancien chemin menant a la station la plus proche
        all_paths_to_station.erase(min_value.first);
        // On rajoute le nouveay chemin le plus proche menant a la station
        all_paths_to_station.insert({min_value.first, the_path});

        /*
        on parcourt toutes les stations qui n'ont pas encore �t� visit�es et on v�rifie si elles sont connect�es � la station actuelle
        qui a �t� visit�e, c'est-�-dire "min_value.first". Si une station "i1" est connect�e � "min_value.first", alors on v�rifie si le
        co�t pour atteindre "i1" depuis "min_value.first" est inf�rieur au co�t actuel de "i1". Si oui, on met � jour le co�t de "i1"
        avec le nouveau co�t plus bas.

        on met �galement � jour le chemin menant � la station "i1" dans la table de hachage "all_paths_to_station". On r�cup�re le chemin
        menant � la station actuelle "min_value.first" de la table de hachage, on supprime le chemin menant � "i1" s'il existe d�j� dans la
        table de hachage, puis on ins�re le nouveau chemin menant � "i1" avec le co�t mis � jour.
        */

        std::unordered_map<uint64_t, uint64_t> station_connect;
        station_connect = this->connections_hashmap[min_value.first];
        for (auto i1 = unvisited_stations.begin(); i1 != unvisited_stations.end(); i1++) {
            for (auto i = station_connect.begin(); i != station_connect.end(); i++) {
                if (i->first == i1->first) {
                    if (i1->second > (i->second + min_value.second)) {
                        i1->second = i->second + min_value.second;
                        the_path = all_paths_to_station.at(min_value.first);
                        all_paths_to_station.erase(i->first);
                        all_paths_to_station.insert({i->first, the_path});
                    }
                }
            }
        }
    }

    the_path = all_paths_to_station.at(_end);
    return the_path;
}


/** Calcul du meillleur itin�raire en utilisant l'agorithme de djikstra impl�ment� pr�c�demment et son affichage
**/

std::vector < std::pair < uint64_t, uint64_t >> Path::compute_and_display_travel(uint64_t _start, uint64_t _end) {
    std::cout << std::endl;
    std::cout << "Le meilleur itineraire de la " << this -> stations_hashmap.at(_start) << " a la " << this -> stations_hashmap.at(_end) << " est: " << std::endl << std::endl;
    std::vector < std::pair < uint64_t, uint64_t >> path;
    //Calcul du meilleur itineraire par djikstra
    path = compute_travel(_start, _end);
    Station station1;
    Station station2;

    //iterateurs
    auto i1 = path.begin();
    auto i2 = i1 + 1;

    while (i2 != path.end()) {
        // R�cup�ration de la premi�re station
        station1 = this -> stations_hashmap[i1 -> first];
        // R�cup�ration de la deuxi�me station
        station2 = this -> stations_hashmap[i2 -> first];
        if (station1.name == station2.name) { // Si les deux stations ont le m�me nom
            if (station1.line_id != station2.line_id) { // Si les deux stations sont sur des lignes diff�rentes
                 // Affichage des informations de marche
                std::cout << "- Marchez jusqu'a " << station2 << " ( " << (i2 -> second - i1 -> second) << " secondes de marche)" << std::endl << std::endl;;
            }
            i1++; i2++;
        // Si les deux stations ont des noms diff�rents
        } else {
            if (station1.line_id == station2.line_id) { // Si les deux stations sont sur la m�me ligne
                if (i2 == path.end() - 1) { // Si c'est la derni�re station de l'itin�raire
                    std::cout << "- Prenez la ligne " << station1.line_id << station1.line_name << std::endl; // Affichage des informations de prise de ligne
                    if ((i2 -> second - (i2 - 1) -> second) == 0) { // Si le temps de trajet entre les deux stations est de 0
                        // Affichage des informations de trajet entre les stations
                        std::cout << "  De " << station1.name << " � " << this -> stations_hashmap.at(i2 -> first).name << " ( " <<  (i2 - i1 - 1) << " stations )  " << std::endl << std::endl;
                    } else {
                        // Affichage des informations de trajet entre les stations
                        std::cout << "  De " << station1.name << " � " << this -> stations_hashmap.at(i2 -> first).name << " ( " << (i2 - i1) << " stations )  "  << std::endl << std::endl;
                    }
                }
                i2++;
                // Si les deux stations sont sur des lignes diff�rentes
            } else {
                 // Affichage des informations de prise de ligne
                std::cout << "- Prenez la ligne " << station1.line_id << station1.line_name << std::endl;
                std::cout << "  De " << station1.name << " a " << this -> stations_hashmap.at((i2 - 1) -> first).name << " ( " << (i2 - i1 - 1)  << " stations )  " <<  std::endl << std::endl;
                i1 = i2 - 1;
            }
        }

    }

    std::cout << "Arrivee a destination estimee a : " << (((path.end() - 1) -> second) / 60) + 1 << " minutes " << std::endl;

    return std::vector < std::pair < uint64_t, uint64_t >> ();
}


// Surcharge de la m�thode compute_travel

std::vector<std::pair<uint64_t, uint64_t>> Path::compute_travel(const std::string& _start, const std::string& _end) {
    // Trouver les identifiants des stations d'entr�e
    uint64_t start_id = 0, end_id = 0;
    std::for_each(this->stations_hashmap.begin(), this->stations_hashmap.end(),
        [&start_id, &_start, &end_id, &_end](const std::pair<uint64_t, Station>& station) {
            if (station.second.name == _start) start_id = station.first;
            if (station.second.name == _end) end_id = station.first;
        }
    );

    // V�rifier que les stations ont �t� trouv�es
    if (!start_id || !end_id) throw std::string("Stations introuvables");

    // Appeler la version avec les identifiants num�riques des stations
    return compute_travel(start_id, end_id);
}

// Surcharge de la methode compute_and_display_travel

std::vector<std::pair<uint64_t, uint64_t>> Path::compute_and_display_travel(const std::string& _start, const std::string& _end) {
    uint64_t start_id = 0, end_id = 0;
    // Trouver les identifiants des stations d'entr�e
    for(const auto station : this->stations_hashmap){
        if(station.second.name == _start){
           start_id = station.first;
        }

        if(station.second.name == _end){
            end_id = station.first;
        }
    }

     // V�rifier que les stations ont �t� trouv�es
    if(!start_id || !end_id) throw std::string("Stations introuvables");

    // Appeler la version avec les identifiants num�riques des stations
    return compute_and_display_travel(start_id, end_id);
}


