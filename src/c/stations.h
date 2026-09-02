/* 
 * This file is part of the Trein Pebble app distribution (https://github.com/guusbeckett/trein-pebble).
 * Copyright (c) 2025 Guus Beckett.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once
#include <pebble.h>

// Struct to hold station information
typedef struct {
  const char* code;
  const char* name;
} Station;

// Struct to map a letter to its list of stations
typedef struct {
    char letter;
    int start_index;
    int count;
} AlphabetIndex;

// The top 15 busiest stations in the Netherlands
static const Station top_stations[] = {
    {"UT", "Utrecht Centraal"}, {"ASD", "Amsterdam C"}, {"RTD", "Rotterdam C"},
    {"GVC", "Den Haag Cen"}, {"SHL", "Schiphol Airport"}, {"EHV", "Eindhoven Cen"},
    {"LEDN", "Leiden Centraal"}, {"AH", "Arnhem Centraal"}, {"HT", "Den Bosch"},
    {"AMF", "Amersfoort Cen"}, {"BD", "Breda"}, {"ZL", "Zwolle"},
    {"GN", "Groningen"}, {"NM", "Nijmegen"}, {"MT", "Maastricht"}
};
#define NUM_TOP_STATIONS (sizeof(top_stations) / sizeof(Station))

// --- Full list of stations, sorted alphabetically ---
static const Station all_stations[] = {
    {"ATN", "Aalten"},{"AC", "Abcoude"},{"AKM", "Akkrum"},{"RTA", "Alexander"},{"AMRN", "Alkmaar Noord"},{"AMR", "Alkmaar"},{"AML", "Almelo"},{"ALM", "Almere Centrum"},{"APN", "Alphen"},{"AMF", "Amersfoort Cen"},{"ASA", "Amstel"},{"ASD", "Amsterdam C"},{"ASDZ", "Amsterdam Zuid"},{"ANA", "Anna Paulowna"},{"APD", "Apeldoorn"},{"APG", "Appingedam"},{"AKL", "Arkel"},{"ARN", "Arnemuiden"},{"AH", "Arnhem Centraal"},{"AHZ", "Arnhem Zuid"},{"ASN", "Assen"},{"SDTB", "Baanhoek"},{"BRN", "Baarn"},{"BF", "Baflo"},{"BRD", "Barendrecht"},{"BNC", "Barneveld Cen"},{"BNN", "Barneveld N"},{"BNZ", "Barneveld Zuid"},{"BDM", "Bedum"},{"BK", "Beek-Elsloo"},{"BSD", "Beesd"},{"BL", "Beilen"},{"BGN", "Bergen op Zoom"},{"BET", "Best"},{"BV", "Beverwijk"},{"ASB", "Bijlmer Arena"},{"BHV", "Bilthoven"},{"RTB", "Blaak"},{"HBZM", "Blauwe Zoom"},{"BR", "Blerick"},{"BLL", "Bloemendaal"},{"BDG", "Bodegraven"},{"BN", "Borne"},{"BSK", "Boskoop"},{"BHDV", "Boven-Hardinxv"},{"BKF", "Bovenkerk Flora"},{"BKG", "Bovenkerk-Gld"},{"BMR", "Boxmeer"},{"BTL", "Boxtel"},{"HMBV", "Brandevoort"},{"BD", "Breda"},{"BKL", "Breukelen"},{"HMBH", "Brouwhuis"},{"BMN", "Brummen"},{"ALMB", "Buiten"},{"BP", "Buitenpost"},{"BDE", "Bunde"},{"BNK", "Bunnik"},{"BSMZ", "Bussum Zuid"},{"LWC", "Camminghaburen"},{"HTNC", "Castellum"},{"CAS", "Castricum"},{"CVM", "Chevremont"},{"CO", "Coevorden"},{"DVC", "Colmschate"},{"CK", "Cuijk"},{"CL", "Culemborg"},{"DA", "Daarlerveen"},{"DLN", "Dalen"},{"DL", "Dalfsen"},{"DEI", "Deinum"},{"DDN", "Delden"},{"DTCP", "Delft Campus"},{"DT", "Delft"},{"DZW", "Delfzijl West"},{"DZ", "Delfzijl"},{"HT", "Den Bosch"},{"DLD", "Den Dolder"},{"GVC", "Den Haag Cen"},{"HDR", "Den Helder"},{"DN", "Deurne"},{"DV", "Deventer"},{"DID", "Didam"},{"DMNZ", "Diemen Zuid"},{"DMN", "Diemen"},{"DR", "Dieren"},{"HTO", "Den Bosch Oost"},{"GV", "Den Haag HS"},{"HDRZ", "Den Helder Z"},{"DTC", "Doetinchem"},{"DDZD", "Dordrecht Zuid"},{"DDR", "Dordrecht"},{"DB", "Driebergen-Zgn"},{"DRH", "Driehuis"},{"DRP", "Dronryp"},{"DRON", "Dronten"},{"DVN", "Duiven"},{"DVD", "Duivendrecht"},{"NMD", "Dukenburg"},{"EC", "Echt"},{"EDC", "Ede Centrum"},{"ED", "Ede-Wageningen"},{"EEM", "Eemshaven"},{"EDN", "Eijsden"},{"EHV", "Eindhoven Cen"},{"EST", "Elst"},{"EMNZ", "Emmen Zuid"},{"EMN", "Emmen"},{"EKZ", "Enkhuizen"},{"ES", "Enschede"},{"EML", "Ermelo"},{"ESE", "Eschmarke"},{"ETN", "Etten-Leur"},{"GERP", "Europapark"},{"EGHM", "Eygelshoven M"},{"EGH", "Eygelshoven"},{"FWD", "Feanwâlden"},{"FN", "Franeker"},{"GDR", "Gaanderen"},{"GDM", "Geldermalsen"},{"GP", "Geldrop"},{"GLN", "Geleen Oost"},{"LUT", "Geleen-Luttrd"},{"HGLG", "Gezondheidspark"},{"GZ", "Gilze-Rijen"},{"GBR", "Glanerbrug"},{"GS", "Goes"},{"NMGO", "Goffert"},{"GO", "Goor"},{"GR", "Gorinchem"},{"GD", "Gouda"},{"GDG", "Gouda Goverwel"},{"GBG", "Gramsbergen"},{"GK", "Grijpskerk"},{"GN", "Groningen"},{"GNN", "Groningen N"},{"GW", "Grou-Jirnsum"},{"HLM", "Haarlem"},{"HWZB", "Halfweg-Zwanb"},{"HDE", "'t Harde"},{"HDB", "Hardenberg"},{"HD", "Harderwijk"},{"GND", "Hardinxveld"},{"HRN", "Haren"},{"HLGH", "Harlingen H"},{"HLG", "Harlingen"},{"HK", "Heemskerk"},{"HAD", "Heemstede-Aerd"},{"HR", "Heerenveen"},{"HWD", "Heerhugowaard"},{"HRLW", "Heerlen West"},{"HRL", "Heerlen"},{"HZE", "Heeze"},{"HLO", "Heiloo"},{"HNO", "Heino"},{"HM", "Helmond"},{"HMN", "Hemmen-Dodew"},{"HGLO", "Hengelo Oost"},{"HGL", "Hengelo"},{"NMH", "Heyendaal"},{"HIL", "Hillegom"},{"HVS", "Hilversum"},{"HNP", "Hindeloopen"},{"HB", "Hoensbroek"},{"HVL", "Hoevelaken"},{"HOR", "Holendrecht"},{"ASHD", "Hollandsche R"},{"HON", "Holten"},{"HFD", "Hoofddorp"},{"HGV", "Hoogeveen"},{"HGZ", "Hoogezand-Sapp"},{"HKS", "Hoogkarspel"},{"HNK", "Hoorn Kersenbg"},{"HN", "Hoorn"},{"HRT", "Horst-Sevenum"},{"HMH", "'t Hout"},{"HTN", "Houten"},{"SGL", "Houthem-St Grl"},{"DTCH", "De Huet"},{"HDG", "Hurdegaryp"},{"IJT", "IJlst"},{"KPNZ", "Kampen Zuid"},{"KPN", "Kampen"},{"BZL", "Kapelle-Biezelg"},{"ESK", "Kennispark"},{"KRD", "Kerkrade Cen"},{"KTR", "Kesteren"},{"KBK", "Klarenbeek"},{"KMR", "Klimmen-Ransdl"},{"KLP", "De Klomp"},{"ZDK", "Kogerveld"},{"KZ", "Koog aan de Zn"},{"KMW", "Koudum-Molkwrm"},{"KBD", "Krabbendijke"},{"KMA", "Krommenie-Assnl"},{"KW", "Kropswolde"},{"KRG", "Kruiningen-Yrs"},{"LAA", "Laan v NOI"},{"ZLW", "Lage Zwaluwe"},{"LG", "Landgraaf"},{"LLZM", "Lansingerland"},{"LDM", "Leerdam"},{"LW", "Leeuwarden"},{"LEDN", "Leiden Centraal"},{"LDL", "Leiden Lammens"},{"UTLR", "Leidsche Rijn"},{"ASDL", "Lelylaan"},{"LLS", "Lelystad Cen"},{"NML", "Lent"},{"LTV", "Lichtenvde-Gld"},{"LC", "Lochem"},{"RLB", "Lombardijen"},{"LP", "Loppersum"},{"UTLN", "Lunetten"},{"LTN", "Lunteren"},{"MZ", "Maarheeze"},{"MRN", "Maarn"},{"MAS", "Maarssen"},{"MTN", "Maastricht N"},{"MT", "Maastricht"},{"UTM", "Maliebaan"},{"MG", "Mantgum"},{"GVM", "Mariahoeve"},{"MRB", "Mariënberg"},{"MTH", "Martenshoek"},{"APDM", "De Maten"},{"HVSM", "Media Park"},{"MES", "Meerssen"},{"MP", "Meppel"},{"MDB", "Middelburg"},{"GVMW", "Moerwijk"},{"MMLH", "Mook-Molenhoek"},{"ASDM", "Muiderpoort"},{"ALMM", "Muziekwijk"},{"NDB", "Naarden-Bussum"},{"NWK", "Nieuwerkerk"},{"NKK", "Nijkerk"},{"NM", "Nijmegen"},{"NVD", "Nijverdal"},{"NS", "Nunspeet"},{"NH", "Nuth"},{"NA", "Nieuw A'dam"},{"NVP", "Nieuw Vennep"},{"NSCH", "Nieuwe Schans"},{"OBD", "Obdam"},{"OT", "Oisterwijk"},{"ODZ", "Oldenzaal"},{"OST", "Olst"},{"OMN", "Ommen"},{"OTB", "Oosterbeek"},{"ALMO", "Oostvaarders"},{"OP", "Opheusden"},{"OW", "Oss West"},{"O", "Oss"},{"APDO", "Osseveld"},{"ODB", "Oudenbosch"},{"UTO", "Overvecht"},{"OVN", "Overveen"},{"PMO", "Overwhere"},{"ALMP", "Parkwijk"},{"TPSW", "Passewaay"},{"AMPO", "Poort"},{"AHPR", "Presikhaaf"},{"BDPB", "Prinsenbeek"},{"PMR", "Purmerend"},{"PT", "Putten"},{"RAT", "Raalte"},{"RAI", "RAI"},{"MTR", "Randwyck"},{"RVS", "Ravenstein"},{"TBR", "Reeshof"},{"RV", "Reuver"},{"RH", "Rheden"},{"RHN", "Rhenen"},{"AMRI", "De Riet"},{"RSN", "Rijssen"},{"RSW", "Rijswijk"},{"RB", "Rilland-Bath"},{"RM", "Roermond"},{"RD", "Roodeschool"},{"RSD", "Roosendaal"},{"RS", "Rosmalen"},{"RTD", "Rotterdam C"},{"RTN", "Rotterdam N"},{"RTZ", "Rotterdam Zuid"},{"RL", "Ruurlo"},{"SPTN", "Santpoort N"},{"SPTZ", "Santpoort Zuid"},{"SSH", "Sassenheim"},{"SWD", "Sauwerd"},{"SGN", "Schagen"},{"SDA", "Scheemda"},{"SDM", "Schiedam Cen"},{"SOG", "Schin op Geul"},{"SN", "Schinnen"},{"SHL", "Schiphol Airpt"},{"CPS", "Scholllevaar"},{"AMFS", "Schothorst"},{"ASSP", "Science Park"},{"STD", "Sittard"},{"SDT", "Sliedrecht"},{"ASS", "Sloterdijk"},{"SKND", "Sneek Noord"},{"SK", "Sneek"},{"BSKS", "Snijdelwijk"},{"STZ", "Soest Zuid"},{"ST", "Soest"},{"SD", "Soestdijk"},{"VSS", "Souburg"},{"HLMS", "Spaarnwoude"},{"SBK", "Spaubeek"},{"HVSP", "Sportpark"},{"RTST", "Stadion"},{"ZLSH", "Stadshagen"},{"DDRS", "Stadspolders"},{"STV", "Stavoren"},{"STM", "Stedum"},{"SWK", "Steenwijk"},{"EHS", "Strijp-S"},{"SRN", "Susteren"},{"SM", "Swalmen"},{"TG", "Tegelen"},{"TBG", "Terborg"},{"UTT", "Terwijde"},{"TL", "Tiel"},{"TBU", "Tilburg Uni"},{"TB", "Tilburg"},{"WADT", "Triangel"},{"TWL", "Twello"},{"UTG", "Uitgeest"},{"UHZ", "Uithuizen"},{"UHM", "Uithuizermeden"},{"UST", "Usquert"},{"UT", "Utrecht Cen"},{"UTVR", "Vaartsche Rijn"},{"VK", "Valkenburg"},{"VSV", "Varsseveld"},{"AVAT", "Vathorst"},{"VDM", "Veendam"},{"VNDC", "Veenendaal Cen"},{"VNDW", "Veenendaal West"},{"VP", "Velp"},{"AHP", "Velperpoort"},{"VL", "Venlo"},{"VRY", "Venray"},{"DVNK", "De Vink"},{"VLB", "Vierlingsbk"},{"VTN", "Vleuten"},{"VS", "Vlissingen"},{"VDL", "Voerendaal"},{"VB", "Voorburg"},{"VH", "Voorhout"},{"VST", "Voorschoten"},{"VEM", "Voorst-Empe"},{"VD", "Vorden"},{"VZ", "Vriezenveen"},{"VHP", "Vroomshoop"},{"VG", "Vught"},{"WADN", "Waddinxveen N"},{"WAD", "Waddinxveen"},{"WFM", "Warffum"},{"WT", "Weert"},{"WP", "Weesp"},{"WL", "Wehl"},{"PMW", "Weidevenne"},{"DWE", "Westereen"},{"WTV", "Westervoort"},{"WZ", "Wezep"},{"WDN", "Wierden"},{"WC", "Wijchen"},{"WH", "Wijhe"},{"WS", "Winschoten"},{"WSM", "Winsum"},{"WWW", "Winterswijk W"},{"WW", "Winterswijk"},{"WD", "Woerden"},{"WF", "Wolfheze"},{"WV", "Wolvega"},{"WK", "Workum"},{"WM", "Wormerveer"},{"YPB", "Ypenburg"},{"ZD", "Zaandam"},{"ZZS", "Zaanse Schans"},{"ZBM", "Zaltbommel"},{"ZVT", "Zandvoort"},{"ZA", "Zetten-Andelst"},{"ZV", "Zevenaar"},{"ZVB", "Zevenbergen"},{"ZTM", "Zoetermeer"},{"ZTMO", "Zoetermeer O"},{"ZB", "Zuidbroek"},{"ZH", "Zuidhorn"},{"UTZL", "Zuilen"},{"ZP", "Zutphen"},{"ZWD", "Zwijndrecht"},{"ZL", "Zwolle"}
};
#define NUM_STATIONS (sizeof(all_stations) / sizeof(Station))

// --- Alphabetical Index ---
// This tells the app where each letter's stations start in the big list and how many there are.
static const AlphabetIndex alphabet_index[] = {
    {'A', 0, 21}, {'B', 21, 38}, {'C', 59, 8}, {'D', 67, 32},
    {'E', 99, 17}, {'F', 116, 2}, {'G', 118, 19}, {'H', 137, 43},
    {'I', 180, 1}, {'K', 181, 16}, {'L', 197, 18}, {'M', 215, 19},
    {'N', 234, 10}, {'O', 244, 15}, {'P', 259, 7}, {'R', 266, 20},
    {'S', 286, 35}, {'T', 321, 8}, {'U', 329, 5}, {'V', 334, 24},
    {'W', 358, 22}, {'Y', 380, 1}, {'Z', 381    , 15}
};
#define ALPHABET_INDEX_COUNT (sizeof(alphabet_index) / sizeof(AlphabetIndex))