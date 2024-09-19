#pragma once

#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <map>

#include "Generic_station_parser.hpp"
#include "Generic_connection_parser.hpp"
#include "Generic_mapper.hpp"


using namespace travel;


namespace travel {

    class Path : public Generic_mapper {
    public:

    // M�thode qui permet de lire les fichiers stations.csv et s.csv contenant les stations de m�tro de RATP, et qui permet de
    //stocker les informations dans le conteneur std::unordered_map

        virtual void read_stations(const std::string& _filename) override;

    // M�thode qui permet de lire les fichiers connections.csv et c.csv contenant les connections des m�tros de RATP, et qui permet de
    //stocker les informations dans le conteneur std::unordered_map
        virtual void read_connections(const std::string &_filename) override;

    //M�thode qui permet de calculer le plus court chemin d'une station vers une autre en utilisant l'algorithme de Djikstra.
        virtual std::vector < std::pair < uint64_t,uint64_t >> compute_travel(uint64_t _start, uint64_t _end) override;

    // M�thode qui utilise la m�thode pr�c�dente pour calculer le plus court chemin � partir des identifiants des stations de d�part et d'arriv�e
    //puis affiche le r�sultat
        virtual std::vector < std::pair < uint64_t,uint64_t >> compute_and_display_travel(uint64_t _start, uint64_t _end) override;

    // Surcharge de la m�thode compute_travel pour pouvoir utiliser le nom des stations � la place des identifiants
        virtual std::vector<std::pair<uint64_t, uint64_t> > compute_travel(const std::string& _start, const std::string& _end) override;

    // Surcharge de la m�thode compute_and_display_travel pour pouvoir utiliser les noms des stations au lieu des identifiants
        virtual std::vector<std::pair<uint64_t, uint64_t> > compute_and_display_travel(const std::string& _start, const std::string& _end) override;

    };

}















