#include <iostream>
#include <string>
#include <regex>
using namespace std;

bool cuiIsValid(const string &cui) {
    if (cui.empty()) {
        cout<<"CUI vacio"<<endl;
        return true;
    }

	//validad la escritura del cui
    regex cuiRegExp(R"(^[0-9]{4}\s?[0-9]{5}\s?[0-9]{4}$)");

    if (!regex_match(cui, cuiRegExp)){
        cout<<"CUI con formato invalido"<<endl;
        return false;
    }

	//separamos por porciones el cui para validar sus respectivas partes
    string formattedCui = regex_replace(cui, regex("\\s"), "");
    int depto = stoi(formattedCui.substr(9, 2));
    int muni = stoi(formattedCui.substr(11, 2));
    string numero = formattedCui.substr(0, 8);
    int verificador = stoi(formattedCui.substr(8, 1));

	//listado de los departamentos con su cantidad de municipios
    int munisPorDepto[] = {
        /* 01 - Guatemala tiene:      */ 17 /* municipios. */,
        /* 02 - El Progreso tiene:    */  8 /* municipios. */,
        /* 03 - Sacatepéquez tiene:   */ 16 /* municipios. */,
        /* 04 - Chimaltenango tiene:  */ 16 /* municipios. */,
        /* 05 - Escuintla tiene:      */ 13 /* municipios. */,
        /* 06 - Santa Rosa tiene:     */ 14 /* municipios. */,
        /* 07 - Sololá tiene:         */ 19 /* municipios. */,
        /* 08 - Totonicapán tiene:    */  8 /* municipios. */,
        /* 09 - Quetzaltenango tiene: */ 24 /* municipios. */,
        /* 10 - Suchitepéquez tiene:  */ 21 /* municipios. */,
        /* 11 - Retalhuleu tiene:     */  9 /* municipios. */,
        /* 12 - San Marcos tiene:     */ 30 /* municipios. */,
        /* 13 - Huehuetenango tiene:  */ 32 /* municipios. */,
        /* 14 - Quiché tiene:         */ 21 /* municipios. */,
        /* 15 - Baja Verapaz tiene:   */  8 /* municipios. */,
        /* 16 - Alta Verapaz tiene:   */ 17 /* municipios. */,
        /* 17 - Petén tiene:          */ 14 /* municipios. */,
        /* 18 - Izabal tiene:         */  5 /* municipios. */,
        /* 19 - Zacapa tiene:         */ 11 /* municipios. */,
        /* 20 - Chiquimula tiene:     */ 11 /* municipios. */,
        /* 21 - Jalapa tiene:         */  7 /* municipios. */,
        /* 22 - Jutiapa				  */ 17 /* municipios. */
    };
	
	//si el numicipio es solo un dato nulo
    if (depto == 0 || muni == 0){
        cout<<"CUI con codigo de municipio o departamento invalido."<<endl;
        return false;
    }
	
	//di el codigo de departamento pasa la cantidad de 22 departamentos (penultimos dos numeros del dpi)
    if (depto > sizeof(munisPorDepto) / sizeof(munisPorDepto[0])){
        cout<<"CUI con codigo de departamento invalido."<<endl;
        return false;
    }
	
	//valida que el codigo de municipio sea el correcto (ultimos dos numeros del dpi)
    if (muni > munisPorDepto[depto - 1]){
        cout<<"CUI con codigo de municipio invalido."<<endl;
        return false;
    }

    // Se verifica el correlativo con base en el algoritmo del complemento 11.
    int total = 0;

    for(int i = 0; i < numero.length(); i++){
        total += (numero[i] - '0') * (i + 2);
    }

    int modulo = (total % 11);

    cout<<"CUI con modulo: "<<modulo<<endl;
    return modulo == verificador;
}

int main() {
    string cui;
    cout<<"Ingrese el CUI: ";
    cin>>cui;

    if(cuiIsValid(cui)){
        cout<<"El CUI es valido."<<endl;
    } else {
        cout<<"El CUI no es valido."<<endl;
    }
    
    return 0;
}

